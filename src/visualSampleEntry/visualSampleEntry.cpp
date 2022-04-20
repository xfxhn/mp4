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


    /*预留 16个字节*/
    bs.readMultiBit(16);
    bs.readMultiBit(16);
    bs.readMultiBit(32);
    bs.readMultiBit(32);
    bs.readMultiBit(32);
    /*width、height：视频的宽高，单位是像素*/
    width = bs.readMultiBit(16);
    height = bs.readMultiBit(16);

    /*一个视频图像在单位尺寸内有多少像素点，像素点越多就越清晰，反之则清晰度越低*/
    /*每英寸的像素值(dpi)，[16.16]格式的数据。*/
    /*horizresolution、vertresolution：水平、垂直方向的分辨率（像素/英寸），16.16定点数，默认是0x00480000（72dpi）*/
    horizresolution = bs.readMultiBit(16) + (static_cast<double>(bs.readMultiBit(16)) / 100000);
    vertresolution = bs.readMultiBit(16) + (static_cast<double>(bs.readMultiBit(16)) / 100000);

    bs.readMultiBit(32);
    /*一个sample中包含多少个frame，对video track来说，默认是1*/
    frame_count = bs.readMultiBit(16);

    /*仅供参考的名字，通常用于展示，占32个字节，比如 AVC Coding。
     * 第一个字节，表示这个名字实际要占用N个字节的长度。第2到第N+1个字节，存储这个名字。
     * 第N+2到32个字节为填充字节。compressorname 可以设置为0*/

    uint8_t compressornameSizeNameByte = bs.readMultiBit(8);

    compressorname = new char[compressornameSizeNameByte + 1]();
    bs.getString(compressorname, compressornameSizeNameByte);
    bs.readMultiBit((32 - compressornameSizeNameByte - 1) * 8);

    /*位图的深度信息，比如 0x0018（24），表示不带alpha通道的图片*/
    depth = bs.readMultiBit(16);
    /*保留*/
    bs.readMultiBit(16);


    uint32_t size11 = bs.readMultiBit(32);
    char str[5]{0};
    bs.getString(str, 4);
    int a = 1;

}

