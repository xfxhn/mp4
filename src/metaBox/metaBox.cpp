
#include <cstring>
#include "metaBox.h"
#include "bitStream.h"
#include "handlerBox.h"
#include "unknownBox.h"

MetaBox::MetaBox(BitStream &bs, const char *boxType, uint32_t size)
        : FullBox(bs, boxType, size, true) {
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
        boxes.push_back(new HandlerBox(bs, boxType, boxSize));
    } else {
        boxes.push_back(new UnknownBox(bs, boxType, boxSize));
    }

    return 0;
}

std::vector<Box *> MetaBox::getBoxes() const {
    return boxes;
}

MetaBox::~MetaBox() {
    for (std::vector<Box *>::size_type i = 0; i < boxes.size(); ++i) {
        delete boxes[i];
        boxes[i] = nullptr;
    }
}

