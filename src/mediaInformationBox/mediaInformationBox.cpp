#include <cstring>
#include "mediaInformationBox.h"
#include "bitStream.h"

MediaInformationBox::MediaInformationBox(BitStream &bs, const char *boxType, uint32_t size)
        : Box(bs, boxType, size) {
    uint32_t offset = 0;

    while (offset < size) {
        uint32_t boxSize = bs.readMultiBit(32);
        offset += boxSize;
        char boxTypeName[5] = {0};
        bs.getString(boxTypeName, 4);
        parseBox(bs, boxTypeName, boxSize);
    }
}

int MediaInformationBox::parseBox(BitStream &bs, const char *boxType, uint32_t boxSize) {

    if (strcmp(boxType, "vmhd") == 0) {
        boxes.push_back(VideoMediaHeaderBox(bs, "vmhd", boxSize));
    } else if (strcmp(boxType, "smhd") == 0) {
        boxes.push_back(SoundMediaHeaderBox(bs, "smhd", boxSize));
    } else if (strcmp(boxType, "hmhd") == 0) {
        boxes.push_back(HintMediaHeaderBox(bs, "hmhd", boxSize));
    }
    return 0;
}

VideoMediaHeaderBox::VideoMediaHeaderBox(BitStream &bs, const char *boxType, uint32_t size)
        : FullBox(bs, boxType, size) {

    /* 2个字节，是枚举的值，目前只有0，表示直接对图像进行拷贝（相当于不做处理）*/
    /*Graphicsmode为这个视频轨道指定了一个组合模式，它来自以下枚举集，可以通过派生规范进行扩展:
      Copy = 0拷贝现有映像
      */
    graphicsmode = bs.readMultiBit(16);
    for (unsigned short &val : opcolor) {
        /*Opcolor是一组3种颜色值(红，绿，蓝)可用于图形模式  */
        val = bs.readMultiBit(16);
    }
}

SoundMediaHeaderBox::SoundMediaHeaderBox(BitStream &bs, const char *boxType, uint32_t size)
        : FullBox(bs, boxType, size) {
    balance = bs.readMultiBit(16);
    /*保留*/
    bs.readMultiBit(16);
}

HintMediaHeaderBox::HintMediaHeaderBox(BitStream &bs, const char *boxType, uint32_t size)
        : FullBox(bs, boxType, size) {
    /*maxPDUsize给出了这个(提示)流中最大PDU的字节大小*/
    maxPDUsize = bs.readMultiBit(16);
    /*avgPDUsize给出了整个演示的PDU的平均大小*/
    avgPDUsize = bs.readMultiBit(16);
    /*Maxbitrate给出了一秒内任何窗口的最大速率，单位为比特/秒*/
    maxbitrate = bs.readMultiBit(32);
    /*Avgbitrate给出了整个演示的平均速率，单位是比特/秒*/
    avgbitrate = bs.readMultiBit(32);

    /*保留*/
    bs.readMultiBit(32);
}

NullMediaHeaderBox::NullMediaHeaderBox(BitStream &bs, const char *boxType, uint32_t size)
        : FullBox(bs, boxType, size) {

}
