#include <cstring>
#include "movieBox.h"
#include "bitStream.h"

MovieBox::MovieBox(BitStream &bs, const char *boxType, uint32_t size)
        : Box(bs, boxType, size), boxtype(boxType), size(size) {

    uint32_t offset = 0;

    while (offset < size) {
        uint32_t boxSize = bs.readMultiBit(32);
        offset += boxSize;
        char boxTypeName[5] = {0};
        bs.getString(boxTypeName, 4);

        parseBox(bs, boxTypeName, boxSize);
    }
    /*uint32_t boxSize = bs.readMultiBit(32);
    char boxType[5] = {0};
    bs.getString(boxType, 4);

    parseBox(bs, boxType, boxSize);

    boxSize = bs.readMultiBit(32);
    memset(boxType, 0, sizeof(char) * 5);
    bs.getString(boxType, 4);
    parseBox(bs, boxType, boxSize);
    int a = 1;*/
    /*while (true) {
        uint32_t boxSize = bs.readMultiBit(32);

        char boxType[5] = {0};
        bs.getString(boxType, 4);

        parseBox(bs, boxType, boxSize);
    }*/

}

int MovieBox::parseBox(BitStream &bs, const char *boxType, uint32_t boxSize) {

    if (strcmp(boxType, "mvhd") == 0) {
        boxes.push_back(MovieHeaderBox(bs, "mvhd", boxSize));
    } else if (strcmp(boxType, "iods") == 0) {
        boxes.push_back(IODS(bs, "iods", boxSize));
    } else if (strcmp(boxType, "trak") == 0) {

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


    for (uint32_t &val : matrix) {
        val = bs.readMultiBit(32);
    }

    for (uint32_t &val : pre_defined) {
        val = bs.readMultiBit(32);
    }
    next_track_ID = bs.readMultiBit(32);
}

/*MovieHeaderBox::~MovieHeaderBox() {
    int aaaaaaa = 1;
}*/

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
IODS::IODS(BitStream &bs, const char *boxtype, uint32_t size)
        : FullBox(bs, boxtype, size) {
    /*24字节的固定值*/
    /*Audio和Video ProfileLevel方面的描述*/
    bs.readMultiBit((size - 12) * 8);
}
