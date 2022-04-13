#include <cstring>
#include "movieBox.h"
#include "bitStream.h"

MovieBox::MovieBox(BitStream &bs, const char *boxtype, uint32_t size)
        : boxtype(boxtype), size(size) {

    uint32_t boxSize = bs.readMultiBit(32);

    char boxType[5] = {0};
    bs.getString(boxType, 4);

    int aa = 1;
}

int MovieBox::parseBox(BitStream &bs, const char *boxType, uint32_t boxSize) {

    if (strcmp(boxType, "mvhd") == 0) {
        MovieHeaderBox mvhd(bs, "mvhd", boxSize);

        boxes.push_back(mvhd);
    }

    return 0;
}

MovieHeaderBox::MovieHeaderBox(BitStream &bs, const char *boxtype, uint32_t size)
        : FullBox(bs, boxtype, size) {

}
