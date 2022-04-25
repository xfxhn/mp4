#include <cstring>
#include "trackReferenceBox.h"
#include "bitStream.h"

TrackReferenceBox::TrackReferenceBox(BitStream &bs, const char *format, uint32_t size)
        : Box(bs, format, size) {
    while (offset < size) {
        uint32_t boxSize = bs.readMultiBit(32);
        offset += boxSize;
        char boxTypeName[5] = {0};
        bs.getString(boxTypeName, 4);

        parseBox(bs, boxTypeName, boxSize);
    }
}

int TrackReferenceBox::parseBox(BitStream &bs, const char *type, uint32_t boxSize) {
    if (strcmp(type, "chap") == 0) {
        Chap chap(bs, type, boxSize);
    }
    return 0;
}

Chap::Chap(BitStream &bs, const char *type, uint32_t boxSize)
        : Box(bs, type, boxSize) {
    track_ids = bs.readMultiBit(32);
}
