#include <cstring>
#include "movieBox.h"
#include "bitStream.h"

MovieBox::MovieBox(BitStream &bs, const char *boxtype, uint32_t size)
        : boxtype(boxtype), size(size) {

    uint32_t boxSize = bs.readMultiBit(32);

    char boxType[5] = {0};
    bs.getString(boxType, 4);

    parseBox(bs, boxType, boxSize);
}

int MovieBox::parseBox(BitStream &bs, const char *boxType, uint32_t boxSize) {

    if (strcmp(boxType, "mvhd") == 0) {
        MovieHeaderBox mvhd(bs, "mvhd", boxSize);
        boxes.push_back(mvhd);
        boxes.push_back(MovieHeaderBox(bs, "mvhd", boxSize));
    }

    return 0;
}

MovieHeaderBox::MovieHeaderBox(BitStream &bs, const char *boxtype, uint32_t size)
        : FullBox(bs, boxtype, size) {
    if (version == 1) {
        creation_time = bs.readMultiBit(64);
        modification_time = bs.readMultiBit(64);
        timescale = bs.readMultiBit(32);
        duration = bs.readMultiBit(64);
    } else {
        creation_time = bs.readMultiBit(32);
        modification_time = bs.readMultiBit(32);
        timescale = bs.readMultiBit(32);
        duration = bs.readMultiBit(32);
    }

    rate = bs.readMultiBit(16) + (static_cast<float>(bs.readMultiBit(16)) / 100000);
    volume = bs.readMultiBit(8) + (static_cast<float>(bs.readMultiBit(8)) / 1000);

    /*保留*/
    bs.readMultiBit(16);
    bs.readMultiBit(32);
    bs.readMultiBit(32);


    for (uint32_t &i : matrix) {
        i = bs.readMultiBit(32);
    }

    for (uint32_t &j : pre_defined) {
        j = bs.readMultiBit(32);
    }
    next_track_ID = bs.readMultiBit(32);
}

MovieHeaderBox::~MovieHeaderBox() {
    int aaaaaaa = 1;
}

MovieHeaderBox::MovieHeaderBox(const MovieHeaderBox &val) : FullBox(val) {
    creation_time = val.next_track_ID;
    modification_time = val.next_track_ID;
    timescale = val.next_track_ID;
    duration = val.next_track_ID;
    rate = val.next_track_ID;
    volume = val.next_track_ID;
    memcpy(matrix, val.matrix, sizeof(uint32_t) * 9);
    memcpy(pre_defined, val.pre_defined, sizeof(uint32_t) * 6);
    next_track_ID = val.next_track_ID;
}

/*MovieHeaderBox::MovieHeaderBox(MovieHeaderBox &&a): FullBox(a.bs,a.boxtype, size) noexcept {

}*/
