#include <cstring>
#include "trackBox.h"
#include "bitStream.h"

TrackBox::TrackBox(BitStream &bs, const char *boxType, uint32_t size)
        : Box(bs, boxType, size) {


    uint32_t boxSize = bs.readMultiBit(32);;
    char boxTypeName[5] = {0};
    bs.getString(boxTypeName, 4);
    parseBox(bs, boxTypeName, boxSize);
    int a = 1;
}

int TrackBox::parseBox(BitStream &bs, const char *boxType, uint32_t boxSize) {
    if (strcmp(boxType, "tkhd") == 0) {
        TrackHeaderBox tkhd(bs, boxType, boxSize);
        boxes.push_back(tkhd);
    }

    return 0;
}


TrackHeaderBox::TrackHeaderBox(BitStream &bs, const char *boxType, uint32_t size)
        : FullBox(bs, boxType, size) {
    if (version == 1) {
        creation_time = bs.readMultiBit(64);
        modification_time = bs.readMultiBit(64);
        track_ID = bs.readMultiBit(32);
        /*保留*/
        bs.readMultiBit(32);
        duration = bs.readMultiBit(64);
    } else {
        creation_time = bs.readMultiBit(32);
        modification_time = bs.readMultiBit(32);
        track_ID = bs.readMultiBit(32);
        /*保留*/
        bs.readMultiBit(32);
        duration = bs.readMultiBit(32);
    }

    /*保留*/
    bs.readMultiBit(32);
    bs.readMultiBit(32);

    layer = bs.readMultiBit(16);
    alternate_group = bs.readMultiBit(16);
    /*根据是视频轨道，还是音频轨道，赋不同的值（需要先处理 hdlr，然后再回来处理这个值）*/
    /*{if track_is_audio 0x0100 else 0}*/
    volume = bs.readMultiBit(8) + (static_cast<float>(bs.readMultiBit(8)) / 1000);

    bs.readMultiBit(16);

    for (unsigned int &val : matrix) {
        val = bs.readMultiBit(32);
    }

    width = bs.readMultiBit(16) + (static_cast<float>(bs.readMultiBit(16)) / 100000);
    height = bs.readMultiBit(16) + (static_cast<float>(bs.readMultiBit(16)) / 100000);

}
