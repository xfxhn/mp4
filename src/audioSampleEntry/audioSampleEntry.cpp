#include <cstring>
#include "audioSampleEntry.h"
#include "bitStream.h"
#include "unknownBox.h"

enum List_of_Class_Tags_for_Descriptors {
    Forbidden = 0x00,
    ObjectDescrTag = 0x01,
    InitialObjectDescrTag = 0x02,
    ES_DescrTag = 0x03,
    DecoderConfigDescrTag = 0x04,
    DecSpecificInfoTag = 0x05,
    SLConfigDescrTag = 0x06,
    ContentIdentDescrTag = 0x07
    /*还有很多，具体参看 mpeg-1 Table 1*/
};

AudioSampleEntry::AudioSampleEntry(BitStream &bs, const char *codingname, uint32_t size)
        : SampleEntry(bs, codingname, size) {
    bs.readMultiBit(32);
    bs.readMultiBit(32);
    offset += 8;
    channelcount = bs.readMultiBit(16);
    /*每个采样点的位深度，也就是一个采样点多少位，一般16bit*/
    samplesize = bs.readMultiBit(16);
    offset += 4;
    bs.readMultiBit(16);
    bs.readMultiBit(16);
    offset += 4;

    samplerate = bs.readMultiBit(32) >> 16u;
    offset += 4;

    while (offset < size) {
        uint32_t boxSize = bs.readMultiBit(32);
        offset += boxSize;
        char boxTypeName[5] = {0};
        bs.getString(boxTypeName, 4);

        parseBox(bs, boxTypeName, boxSize);
    }
}

int AudioSampleEntry::parseBox(BitStream &bs, const char *boxType, uint32_t boxSize) {

    if (strcmp(boxType, "esds") == 0) {
        boxes.push_back(new esdsConfigurationBox(bs, boxType, boxSize));
    } else {
        boxes.push_back(new UnknownBox(bs, boxType, boxSize));
    }
    return 0;
}

std::vector<Box *> AudioSampleEntry::getBoxes() const {
    return boxes;
}

AudioSampleEntry::~AudioSampleEntry() {
    for (std::vector<Box *>::size_type i = 0; i < boxes.size(); ++i) {
        delete boxes[i];
        boxes[i] = nullptr;
    }
}

esdsConfigurationBox::esdsConfigurationBox(BitStream &bs, const char *type, uint32_t size)
        : FullBox(bs, type, size) {
    uint8_t separator[3]{0};
    while (offset < size) {
        uint8_t tag = bs.readMultiBit(8);
        offset += 1;
        separator[0] = bs.readMultiBit(8);
        separator[1] = bs.readMultiBit(8);
        separator[2] = bs.readMultiBit(8);
        offset += 3;
        /*表示后面还有多少字节 不太确定到底是干嘛的*/
        uint8_t tagSize = bs.readMultiBit(8);
        offset += 1;
        parseDescriptor(bs, tag);
    }
}

int esdsConfigurationBox::parseDescriptor(BitStream &bs, uint8_t tag) {
    if (tag == ES_DescrTag) {
        ES_Descriptor(bs);
    } else if (tag == DecoderConfigDescrTag) {
        DecoderConfigDescriptor(bs);
    } else if (tag == DecSpecificInfoTag) {
        DecoderSpecificInfo(bs);
    } else if (tag == SLConfigDescrTag) {
        SLConfigDescriptor(bs);
    }
    return 0;
}

int esdsConfigurationBox::ES_Descriptor(BitStream &bs) {
    /*这个元素为其名称作用域内的每个基本流提供了一个惟一的标签。0和0xFFFF是保留的。*/
    ES_ID = bs.readMultiBit(16);
    offset += 2;
    streamDependenceFlag = bs.readBit();
    URL_Flag = bs.readBit();
    OCRstreamFlag = bs.readBit();
    /*指示此基本流优先级的相对度量。具有较高streamPriority的基本流比具有较低streamPriority的基本流更重要*/
    streamPriority = bs.readMultiBit(5);
    offset += 1;
    if (streamDependenceFlag) {
        /*是该基本流依赖的另一个基本流的ES_ID。带有dependsOn_ES_ID的流也应该与当前ES_Descriptor关联到相同的对象描述符*/
        uint16_t dependsOn_ES_ID = bs.readMultiBit(16);
        offset += 2;
    }
    if (URL_Flag) {
        /*后续url字符串的长度(以字节为单位)*/
        uint8_t URLlength = bs.readMultiBit(8);
        offset += 1;
        char *URLstring = new char[URLlength + 1]();
        /*包含一个UTF-8 (ISO/IEC 10646-1)编码的URL，该URL通过名称指向一个SL-分组流的位置。
         * 从URL检索的sl包化流的参数在这个ES_Descriptor中完全指定*/
        bs.getString(URLstring, URLlength);
        offset += URLlength;
    }
    if (OCRstreamFlag) {
        /*表示命名作用域(参见8.7.2.4)内的基本流的ES_ID，从该作用域派生出该基本流的时间基。不允许在基本流之间循环引用*/
        uint16_t OCR_ES_Id = bs.readMultiBit(16);
        offset += 2;
    }
    return 0;
}

int esdsConfigurationBox::DecoderConfigDescriptor(BitStream &bs) {

    /*参考mepeg-4 part1 Table 8*/
    objectTypeIndication = bs.readMultiBit(8);
    /*参考mpeg-4 part1 Table 9，基本流的类型 一般是5=AudioStream*/
    streamType = bs.readMultiBit(6);
    /*指示此流用于上游信息。  */
    upStream = bs.readMultiBit(1);
    bs.readMultiBit(1);
    offset += 2;

    /*是这个基本流的解码缓冲区的大小，以字节为单位 */
    bufferSizeDB = bs.readMultiBit(24);
    offset += 3;
    /*在任何持续一秒的时间窗口中，该基本流的最大比特率(以每秒位为单位)。*/
    maxBitrate = bs.readMultiBit(32);
    offset += 4;
    /*是基本流的平均比特率，单位是比特/秒。 对于可变比特率的流，这个值应该设置为零*/
    avgBitrate = bs.readMultiBit(32);
    offset += 4;
    return 0;
}

int esdsConfigurationBox::DecoderSpecificInfo(BitStream &bs) {
    /*参见mpeg-4 part3 Table 1.17 2是AAC LC*/
    uint8_t bitSize = 5;
    audioObjectType = GetAudioObjectType(bs);
    /*采样率 Table 1.18 如果samplingFrequencyIndex等于15，那么实际的采样率直接由samplingFrequency的值表示 3是48000采样率*/
    samplingFrequencyIndex = bs.readMultiBit(4);
    bitSize += 4;
    if (samplingFrequencyIndex == 0xF) {
        samplingFrequency = bs.readMultiBit(24);
        bitSize += 24;
    }

    /*通道数 参见Table 1.19 2是双通道*/
    channelConfiguration = bs.readMultiBit(4);
    bitSize += 4;
    int sbrPresentFlag = -1;
    int psPresentFlag = -1;
    /*是否开启了SBR和PS，这个是在mpeg-2 AAC上的扩展*/
    if (audioObjectType == 5 || audioObjectType == 29) {
        extensionAudioObjectType = 5;
        sbrPresentFlag = 1;
        if (audioObjectType == 29) {
            psPresentFlag = 1;
        }
        extensionSamplingFrequencyIndex = bs.readMultiBit(4);
        bitSize += 4;
        if (extensionSamplingFrequencyIndex == 0xF) {
            extensionSamplingFrequency = bs.readMultiBit(24);
            bitSize += 24;
        }
        /*audioObjectType*/
        uint8_t bitSize1 = 0;
        audioObjectType = GetAudioObjectType(bs);
        bitSize += bitSize1;
        //audioObjectType = type;
        if (audioObjectType == 22) {
            extensionChannelConfiguration = bs.readMultiBit(4);
            bitSize += 4;
        }
    } else {
        extensionAudioObjectType = 0;
    }

    switch (audioObjectType) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 6:
        case 7:
        case 17:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
            GASpecificConfig(bs, bitSize);
            break;
            /*case 8:
                //CelpSpecificConfig();
                break;
            case 9:
                //HvxcSpecificConfig();
                break;
            case 12:
                //TTSSpecificConfig();
                break;
            case 13:
            case 14:
            case 15:
            case 16:
                //StructuredAudioSpecificConfig();
                break;
            case 24:
                //ErrorResilientCelpSpecificConfig();
                break;
            case 25:
                //ErrorResilientHvxcSpecificConfig();
                break;
            case 26:
            case 27:
                //ParametricSpecificConfig();
                break;*/
            //...参考 1.6.2.1 AudioSpecificConfig
    }
    offset += bitSize / 8;
    return 0;
}

/*可以根据每个单个基本流的需要配置SL包报头。可选择的参数包括时间戳和时钟参考的存在性、分辨率和准确性。
 * 这种灵活性允许，例如，一个低比特率的基本流在SL包头上产生很小的开销。*/
int esdsConfigurationBox::SLConfigDescriptor(BitStream &bs) {
    /*允许从一组预定义的参数集默认值. 参见mpeg-4 part1 Table 51   0是自定义*/
    predefined = bs.readMultiBit(8);
    offset += 1;

    /*Table 52 – Detailed predefined SLConfigDescriptor values*/
    /*参考上面 predefined 对应的预定义值*/
    bool durationFlag = false;
    bool useTimeStampsFlag = true;
    uint8_t timeStampLength = 0;
    if (predefined == 0) {
        bool useAccessUnitStartFlag = bs.readBit();
        bool useAccessUnitEndFlag = bs.readBit();
        bool useRandomAccessPointFlag = bs.readBit();
        bool hasRandomAccessUnitsOnlyFlag = bs.readBit();
        bool usePaddingFlag = bs.readBit();
        /*指示时间戳用于此基本流的同步。 它们在SL包报头中传递。
         * 否则，accessUnitRate, compositionUnitRate, startDecodingTimeStamp和startCompositionTimeStamp在这个SL报文头配置应使用中进行同步。  */
        useTimeStampsFlag = bs.readBit();
        bool useIdleFlag = bs.readBit();
        /*指示此基本流的访问单元和组合单元的持续时间不变。*/
        durationFlag = bs.readBit();
        uint32_t timeStampResolution = bs.readMultiBit(32);
        uint32_t OCRResolution = bs.readMultiBit(32);
        /*是SL包头中的时间戳字段的长度。 timeStampLength的值应该在0到64位之间。  */
        timeStampLength = bs.readMultiBit(8); // must be <= 64
        uint8_t OCRLength = bs.readMultiBit(8);       // must be <=  64
        uint8_t AU_Length = bs.readMultiBit(8);       // must be <= 32
        uint8_t instantBitrateLength = bs.readMultiBit(8);
        uint8_t degradationPriorityLength = bs.readMultiBit(4);
        uint8_t AU_seqNumLength = bs.readMultiBit(5); // must be <= 16
        uint8_t packetSeqNumLength = bs.readMultiBit(5); // must be <= 16
        bs.readMultiBit(2);
    }
    if (durationFlag) {
        uint32_t timeScale = bs.readMultiBit(32);
        uint16_t accessUnitDuration = bs.readMultiBit(16);
        uint16_t compositionUnitDuration = bs.readMultiBit(16);
    }
    if (!useTimeStampsFlag) {
        uint8_t startDecodingTimeStamp = bs.readMultiBit(timeStampLength);
        uint8_t startCompositionTimeStamp = bs.readMultiBit(timeStampLength);
    }
    return 0;
}


uint8_t esdsConfigurationBox::GetAudioObjectType(BitStream &bs) {
    uint8_t audioObjectType = bs.readMultiBit(5);
    if (audioObjectType == 31) {
        uint8_t audioObjectTypeExt = bs.readMultiBit(6);
        audioObjectType = 32 + audioObjectTypeExt;
    }
    return audioObjectType;
}

int esdsConfigurationBox::GASpecificConfig(BitStream &bs, uint8_t &bitSize) {
    /*帧的长度，光谱线的数量，分别对于除AAC SSR和ER AAC LD之外的所有通用音频对象类型*/
    /*当设置为0时，IMDCT为1024/128行，framength为1024;当设置为1时，IMDCT为960/120行，framength为960*/
    /*ER AAC LD:设置为0时，IMDCT为512行，framength为512;设置为1时，IMDCT为480行，framength为480*/
    /*对于AAC SSR:必须设置为0。使用256/32线IMDCT。注意:IMDCT的实际行数(第一个或第二个值)由window_sequence的值区分*/
    frameLengthFlag = bs.readBit();
    bitSize += 1;
    /*在可伸缩的AAC配置的底层中使用了核心编码器的信号*/
    dependsOnCoreCoder = bs.readBit();
    bitSize += 1;
    if (dependsOnCoreCoder) {
        /*在MDCT计算之前，必须应用于上采样(必要时)核心解码器输出的样本中的延迟*/
        uint16_t coreCoderDelay = bs.readMultiBit(14);
    }
    /*对于audioObjectType = 1、2、3、4、6、7，应为“0”。audioObjectType = 17,19,20,21,22,23应为' 1 '。*/
    extensionFlag = bs.readBit();
    bitSize += 1;
    //如果是0的话
    if (!channelConfiguration) {
        /*信道到扬声器映射*/
        /*在AOT相关的SpecificConfig中定义*/
        //program_config_element();
    }
    if ((audioObjectType == 6) || (audioObjectType == 20)) {
        /*表示可伸缩配置中的AAC层号。第一个AAC层由值0表示。*/
        uint8_t layerNr = bs.readMultiBit(3);
    }
    if (extensionFlag) {
        if (audioObjectType == 22) {
            uint8_t numOfSubFrame = bs.readMultiBit(5);

            uint16_t layer_length = bs.readMultiBit(11);
        }
        if (audioObjectType == 17 || audioObjectType == 19 ||
            audioObjectType == 20 || audioObjectType == 23) {
            bool aacSectionDataResilienceFlag = bs.readBit();
            bool aacScalefactorDataResilienceFlag = bs.readBit();
            bool aacSpectralDataResilienceFlag = bs.readBit();
        }

        bool extensionFlag3 = bs.readBit();
        if (extensionFlag3) {
            // todoList待定
        }
    }

    return 0;
}








