#include <cstring>
#include "audioSampleEntry.h"
#include "bitStream.h"


AudioSampleEntry::AudioSampleEntry(BitStream &bs, const char *codingname, uint32_t size)
        : SampleEntry(bs, codingname, size) {
    bs.readMultiBit(32);
    bs.readMultiBit(32);
    offset += 8;
    channelcount = bs.readMultiBit(16);
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
        esdsConfigurationBox esds(bs, boxType, boxSize);
    }
    return 0;
}


esdsConfigurationBox::esdsConfigurationBox(BitStream &bs, const char *type, uint32_t size)
        : FullBox(bs, type, size) {
    uint8_t separator[3]{0};

    ES_DescrTag = bs.readMultiBit(8);

    separator[0] = bs.readMultiBit(8);
    separator[1] = bs.readMultiBit(8);
    separator[2] = bs.readMultiBit(8);
    if (separator[0] == 0x80 && separator[1] == 0x80 && separator[2] == 0x80) {
        ESSize = bs.readMultiBit(8);
        ESId = bs.readMultiBit(16);
    } else {
        ESSize = separator[0];
        ESId = (uint16_t) (separator[1] << 8u) | separator[2];
    }
    ESFlag = bs.readMultiBit(8);


    /*参见mpeg-1 Table 1*/
    DecoderConfigDescrTag = bs.readMultiBit(8);
    separator[0] = bs.readMultiBit(8);
    separator[1] = bs.readMultiBit(8);
    separator[2] = bs.readMultiBit(8);
    if (separator[0] == 0x80 && separator[1] == 0x80 && separator[2] == 0x80) {
        DCDSize = bs.readMultiBit(8);
        /*参考mepeg-4 part1 Table 8*/
        objectTypeIndication = bs.readMultiBit(8);
        /*参考mpeg-4 part1 Table 9，基本流的类型 一般是5=AudioStream*/
        streamType = bs.readMultiBit(6);
        /*指示此流用于上游信息。  */
        upStream = bs.readMultiBit(1);
        bs.readMultiBit(1);
    } else {
        DCDSize = separator[0];
        objectTypeIndication = separator[1];
        streamType = ((unsigned) separator[2] >> 2u) & 0x3Fu;
        upStream = ((unsigned) separator[2] >> 1u) & 0x01u;
    }
    /*是这个基本流的解码缓冲区的大小，以字节为单位 */
    bufferSizeDB = bs.readMultiBit(24);
    /*在任何持续一秒的时间窗口中，该基本流的最大比特率(以每秒位为单位)。*/
    maxBitrate = bs.readMultiBit(32);
    /*是基本流的平均比特率，单位是比特/秒。 对于可变比特率的流，这个值应该设置为零*/
    avgBitrate = bs.readMultiBit(32);

    /*AudioSpecificConfig()扩展抽象类DecoderSpecificInfo，在ISO/IEC 14496-1中定义，
     * 当DecoderConfigDescriptor,objectTypeIndication是指符合ISO/IEC 14496-3标准的数据流。
     * 在这种情况下，AudioSpecificConfig()的存在是必须的。*/
    DecSpecificInfoTag = bs.readMultiBit(8);
    separator[0] = bs.readMultiBit(8);
    separator[1] = bs.readMultiBit(8);
    separator[2] = bs.readMultiBit(8);
    if (separator[0] == 0x80 && separator[1] == 0x80 && separator[2] == 0x80) {
        DSDSize = bs.readMultiBit(8);
        /*参见mpeg-4 part3 Table 1.17 2是AAC LC*/
        audioObjectType = GetAudioObjectType(bs);
        /*采样率 Table 1.18 如果samplingFrequencyIndex等于15，那么实际的采样率直接由samplingFrequency的值表示 3是48000采样率*/
        samplingFrequencyIndex = bs.readMultiBit(4);
        if (samplingFrequencyIndex == 0xF) {
            samplingFrequency = bs.readMultiBit(24);
        }

        /*通道数 参见Table 1.19 2是双通道*/
        channelConfiguration = bs.readMultiBit(4);

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
            if (extensionSamplingFrequencyIndex == 0xF) {
                extensionSamplingFrequency = bs.readMultiBit(24);
            }
            audioObjectType = GetAudioObjectType(bs);
            if (audioObjectType == 22) {
                extensionChannelConfiguration = bs.readMultiBit(4);
            }
        } else {
            extensionAudioObjectType = 0;
        }

    } else {
        DSDSize = separator[0];
        audioObjectType = ((unsigned) separator[1]) >> 3u & 0x1Fu;
        if (audioObjectType == 31) {
            uint8_t audioObjectTypeExt = separator[1] & 0x07u;
            uint8_t temp = (unsigned) separator[2] >> 5u & 0x07u;
            audioObjectTypeExt = (unsigned) audioObjectTypeExt << 3u | temp;
            audioObjectType = 32 + audioObjectTypeExt;
        }
        //懒得算了,遇到这种MP4在说
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
            GASpecificConfig(bs);
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
}

uint8_t esdsConfigurationBox::GetAudioObjectType(BitStream &bs) {
    uint8_t audioObjectType = bs.readMultiBit(5);
    if (audioObjectType == 31) {
        uint8_t audioObjectTypeExt = bs.readMultiBit(6);
        audioObjectType = 32 + audioObjectTypeExt;
    }
    return audioObjectType;
}

int esdsConfigurationBox::GASpecificConfig(BitStream &bs) {
    /*帧的长度，光谱线的数量，分别对于除AAC SSR和ER AAC LD之外的所有通用音频对象类型*/
    /*当设置为0时，IMDCT为1024/128行，framength为1024;当设置为1时，IMDCT为960/120行，framength为960*/
    /*ER AAC LD:设置为0时，IMDCT为512行，framength为512;设置为1时，IMDCT为480行，framength为480*/
    /*对于AAC SSR:必须设置为0。使用256/32线IMDCT。注意:IMDCT的实际行数(第一个或第二个值)由window_sequence的值区分*/
    frameLengthFlag = bs.readBit();
    /*在可伸缩的AAC配置的底层中使用了核心编码器的信号*/
    dependsOnCoreCoder = bs.readBit();
    if (dependsOnCoreCoder) {
        /*在MDCT计算之前，必须应用于上采样(必要时)核心解码器输出的样本中的延迟*/
        uint16_t coreCoderDelay = bs.readMultiBit(14);
    }
    /*对于audioObjectType = 1、2、3、4、6、7，应为“0”。audioObjectType = 17,19,20,21,22,23应为' 1 '。*/
    extensionFlag = bs.readBit();

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
