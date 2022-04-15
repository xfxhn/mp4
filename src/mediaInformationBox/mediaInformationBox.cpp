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

    }
    return 0;
}

