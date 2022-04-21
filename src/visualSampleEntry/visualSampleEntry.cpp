#include <cstring>
#include "visualSampleEntry.h"
#include "bitStream.h"

SampleEntry::SampleEntry(BitStream &bs, const char *format, uint32_t size)
        : Box(bs, format, size) {
    /*保留*/
    bs.readMultiBit(48);
    /*当MP4文件的数据部分，可以被分割成多个片段，每一段对应一个索引，并分别通过URL地址来获取，
     * 此时，data_reference_index 指向对应的片段（比较少用到）；*/
    data_reference_index = bs.readMultiBit(16);

}

VisualSampleEntry::VisualSampleEntry(BitStream &bs, const char *codingname, uint32_t size)
        : SampleEntry(bs, codingname, size) {

    /*type 4 size 4 reserved 6 data_reference_index 2*/
    uint32_t offset = 16;
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

    } else if (strcmp(boxType, "colr") == 0) {

    }
    return 0;
}

AVCConfigurationBox::AVCConfigurationBox(BitStream &bs, const char *BoxType, uint32_t size)
        : Box(bs, BoxType, size), AVCConfig(bs) {

}

AVCDecoderConfigurationRecord::AVCDecoderConfigurationRecord(BitStream &bs) {
    configurationVersion = bs.readMultiBit(8);
    AVCProfileIndication = bs.readMultiBit(8);
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
        uint16_t sequenceParameterSetLength = bs.readMultiBit(16);
        uint8_t *sps = new uint8_t[sequenceParameterSetLength];
        memcpy(sps, bs.currentPtr, sequenceParameterSetLength);
        bs.readMultiBit(sequenceParameterSetLength * 8);
    }
}
