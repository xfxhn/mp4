
#include <cstring>
#include "metaBox.h"
#include "bitStream.h"
#include "handlerBox.h"
#include "unknownBox.h"

MetaBox::MetaBox(BitStream &bs, const char *boxType, uint32_t size)
        : FullBox(bs, boxType, size) {
    while (offset < size) {
        uint32_t boxSize = bs.readMultiBit(32);
        offset += boxSize;
        char boxTypeName[5] = {0};
        bs.getString(boxTypeName, 4);
        parseBox(bs, boxTypeName, boxSize);
    }
}

int MetaBox::parseBox(BitStream &bs, const char *boxType, uint32_t boxSize) {
    if (strcmp(boxType, "hdlr") == 0) {
        HandlerBox hdlr(bs, boxType, boxSize);
        boxes.push_back(hdlr);
    } else {
        UnknownBox unkn(bs, boxType, boxSize);
        boxes.push_back(unkn);
    }

    return 0;
}

