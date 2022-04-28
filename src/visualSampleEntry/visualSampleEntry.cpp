#include <cstring>
#include "visualSampleEntry.h"
#include "bitStream.h"


VisualSampleEntry::VisualSampleEntry(BitStream &bs, const char *codingname, uint32_t size)
        : SampleEntry(bs, codingname, size) {

    /*type 4 size 4 reserved 6 data_reference_index 2*/
    /*预留 16个字节*/
    bs.readMultiBit(16);
    bs.readMultiBit(16);
    bs.readMultiBit(32);
    bs.readMultiBit(32);
    bs.readMultiBit(32);
    offset += 16;
    /*width、height：视频的宽高，单位是像素*/
    width = bs.readMultiBit(16);
    height = bs.readMultiBit(16);
    offset += 4;

    /*一个视频图像在单位尺寸内有多少像素点，像素点越多就越清晰，反之则清晰度越低*/
    /*每英寸的像素值(dpi)，[16.16]格式的数据。*/
    /*horizresolution、vertresolution：水平、垂直方向的分辨率（像素/英寸），16.16定点数，默认是0x00480000（72dpi）*/
    horizresolution = bs.readMultiBit(16) + (static_cast<double>(bs.readMultiBit(16)) / 100000);
    vertresolution = bs.readMultiBit(16) + (static_cast<double>(bs.readMultiBit(16)) / 100000);
    offset += 8;

    /*保留*/
    bs.readMultiBit(32);
    offset += 4;

    /*一个sample中包含多少个frame，对video track来说，默认是1*/
    frame_count = bs.readMultiBit(16);
    offset += 2;

    /*仅供参考的名字，通常用于展示，占32个字节，比如 AVC Coding。
     * 第一个字节，表示这个名字实际要占用N个字节的长度。第2到第N+1个字节，存储这个名字。
     * 第N+2到32个字节为填充字节。compressorname 可以设置为0*/
    uint8_t compressornameSizeNameByte = bs.readMultiBit(8);
    compressorname = new char[compressornameSizeNameByte + 1]();
    bs.getString(compressorname, compressornameSizeNameByte);
    bs.readMultiBit((32 - compressornameSizeNameByte - 1) * 8);
    offset += 32;

    /*位图的深度信息，比如 0x0018（24），表示不带alpha通道的图片*/
    depth = bs.readMultiBit(16);
    offset += 2;

    /*保留*/
    bs.readMultiBit(16);
    offset += 2;


    while (offset < size) {
        uint32_t boxSize = bs.readMultiBit(32);
        offset += boxSize;
        char boxTypeName[5] = {0};
        bs.getString(boxTypeName, 4);

        parseBox(bs, boxTypeName, boxSize);
    }


}


int VisualSampleEntry::parseBox(BitStream &bs, const char *boxType, uint32_t boxSize) {

    if (strcmp(boxType, "avcC") == 0) {
        AVCConfigurationBox avcC(bs, boxType, boxSize);
        boxes.push_back(avcC);
    } else if (strcmp(boxType, "uuid") == 0) {
        extendBox uuid(bs, boxType, boxSize);
        boxes.push_back(uuid);
    } else if (strcmp(boxType, "colr") == 0) {
        ColourInformationBox colr(bs, boxType, boxSize);
        boxes.push_back(colr);
    }
    return 0;
}

VisualSampleEntry::~VisualSampleEntry() {
    if (compressorname) {
        delete[] compressorname;
        compressorname = nullptr;
    }
}

AVCConfigurationBox::AVCConfigurationBox(BitStream &bs, const char *BoxType, uint32_t size)
        : Box(bs, BoxType, size), AVCConfig(bs) {

}

AVCDecoderConfigurationRecord::AVCDecoderConfigurationRecord(BitStream &bs) {
    configurationVersion = bs.readMultiBit(8);
    /*编码等级*/
    AVCProfileIndication = bs.readMultiBit(8);
    /*应该是 level_IDC*/
    /*支持的分辨率、最大引用数、帧速率等。见H.264/AVC附件A。*/
    profile_compatibility = bs.readMultiBit(8);
    AVCLevelIndication = bs.readMultiBit(8);
    /*保留*/
    bs.readMultiBit(6);
    lengthSizeMinusOne = bs.readMultiBit(2);
    /*保留*/
    bs.readMultiBit(3);

    /*numOfSequenceParameterSets表示用于解码AVC基本流的初始SPSs集的数量。(sps的个数)*/
    numOfSequenceParameterSets = bs.readMultiBit(5);
    for (int i = 0; i < numOfSequenceParameterSets; ++i) {
        /*sps多少字节*/
        sequenceParameterSetLength[i] = bs.readMultiBit(16);
        sequenceParameterSetNALUnit[i] = new uint8_t[sequenceParameterSetLength[i]]();
        memcpy(sequenceParameterSetNALUnit[i], bs.currentPtr, sequenceParameterSetLength[i]);
        bs.readMultiBit(sequenceParameterSetLength[i] * 8);
    }

    numOfPictureParameterSets = bs.readMultiBit(8);
    for (int j = 0; j < numOfPictureParameterSets; ++j) {
        /*pps多少字节*/
        pictureParameterSetLength[j] = bs.readMultiBit(16);
        pictureParameterSetNALUnit[j] = new uint8_t[pictureParameterSetLength[j]]();
        memcpy(pictureParameterSetNALUnit[j], bs.currentPtr, pictureParameterSetLength[j]);
        bs.readMultiBit(pictureParameterSetLength[j] * 8);
    }

    uint8_t profile_idc = AVCProfileIndication;
    /*
        66	Baseline
        77	Main
        88	Extended
        100	High(FRExt)
        110	High 10 (FRExt)
        122	High 4:2 : 2 (FRExt)
        144	High 4 : 4 : 4 (FRExt)
    */
    if (profile_idc == 100 || profile_idc == 110 || profile_idc == 122 || profile_idc == 144) {
        bs.readMultiBit(6);

        /*chroma_format_idc = 0	单色
        chroma_format_idc = 1	YUV 4 : 2 : 0
        chroma_format_idc = 2	YUV 4 : 2 : 2
        chroma_format_idc = 3	YUV 4 : 4 : 4
        当chroma_format_idc不存在时，它将被推断为等于1(4:2:0色度格式)。*/
        chroma_format = bs.readMultiBit(2);
        bs.readMultiBit(5);
        //亮度用几bit表示，这个值是个偏移（bit位深度）
        /*(BitDepth = 8 + bit_depth_luma_minus8)*/
        bit_depth_luma_minus8 = bs.readMultiBit(3);
        bs.readMultiBit(5);
        /*色度位深度的偏移*/
        bit_depth_chroma_minus8 = bs.readMultiBit(3);
        /*numOfSequenceParameterSetExt表示用于AVC基本流解码的序列参数集扩展的数量*/
        numOfSequenceParameterSetExt = bs.readMultiBit(8);
        for (int i = 0; i < numOfSequenceParameterSetExt; ++i) {
            sequenceParameterSetExtLength[i] = bs.readMultiBit(16);
            sequenceParameterSetExtNALUnit[i] = new uint8_t[sequenceParameterSetExtLength[i]]();
            memcpy(sequenceParameterSetExtNALUnit[i], bs.currentPtr, sequenceParameterSetExtLength[i]);
            bs.readMultiBit(sequenceParameterSetExtLength[i] * 8);
        }
    }


}

AVCDecoderConfigurationRecord::~AVCDecoderConfigurationRecord() {

    for (int i = 0; i < numOfSequenceParameterSets; ++i) {
        if (sequenceParameterSetNALUnit[i]) {
            delete[] sequenceParameterSetNALUnit[i];
            sequenceParameterSetNALUnit[i] = nullptr;
        }
    }

    for (int j = 0; j < numOfPictureParameterSets; ++j) {
        if (pictureParameterSetNALUnit[j]) {
            delete[] pictureParameterSetNALUnit[j];
            pictureParameterSetNALUnit[j] = nullptr;
        }
    }
    for (int j = 0; j < numOfSequenceParameterSetExt; ++j) {
        if (sequenceParameterSetExtNALUnit[j]) {
            delete[] sequenceParameterSetExtNALUnit[j];
            sequenceParameterSetExtNALUnit[j] = nullptr;
        }
    }
}

extendBox::extendBox(BitStream &bs, const char *BoxType, uint32_t size)
        : Box(bs, BoxType, size) {
    uint32_t a = bs.readMultiBit(32);
}

ColourInformationBox::ColourInformationBox(BitStream &bs, const char *BoxType, uint32_t size)
        : Box(bs, BoxType, size) {
/*Colour_type:表示所提供的颜色信息的类型。
 * 对于colour_type ' nclx ':这些字段恰好是在ISO/IEC 29199-2的a .7.2中为PTM_COLOR_INFO()定义的四个字节，
 * 但请注意，全范围标志在这里的不同位位置  */
    bs.getString(colour_type, 4);

    if (strcmp(colour_type, "nclc") == 0) {
        /*参考https://developer.apple.com/library/archive/documentation/QuickTime/QTFF/QTFFChap3/qtff3.html#//apple_ref/doc/uid/TP40000939-CH205-125526*/
        primariesIndex = bs.readMultiBit(16);
        transferFunctionIndex = bs.readMultiBit(16);
        matrixIndex = bs.readMultiBit(16);
    } else if (strcmp(colour_type, "nclx") == 0) {
        colour_primaries = bs.readMultiBit(16);
        transfer_characteristics = bs.readMultiBit(16);
        matrix_coefficients = bs.readMultiBit(16);
        full_range_flag = bs.readBit();
        bs.readMultiBit(7);
    } else if (strcmp(colour_type, "rICC") == 0) {
        /*参考https://blog.csdn.net/lxw907304340/article/details/46356637*/
        /*参考https://blog.csdn.net/culinxia2707/article/details/108781014?spm=1001.2101.3001.6650.6&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-6.pc_relevant_paycolumn_v3&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-6.pc_relevant_paycolumn_v3&utm_relevant_index=10*/
        //ICC_profile
    } else if (strcmp(colour_type, "prof") == 0) {
        /*参考https://blog.csdn.net/lxw907304340/article/details/46356637*/
        //ICC_profile
    }
}
