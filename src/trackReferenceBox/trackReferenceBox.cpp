#include <cstring>
#include "trackReferenceBox.h"
#include "bitStream.h"
#include "unknownBox.h"

TrackReferenceBox::TrackReferenceBox(BitStream &bs, const char *format, uint32_t size)
        : Box(bs, format, size, true) {
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
        boxes.push_back(new Chap(bs, type, boxSize));
    } else {
        boxes.push_back(new UnknownBox(bs, type, boxSize));
    }
    return 0;
}

std::vector<Box *> TrackReferenceBox::getBoxes() const {
    return boxes;
}

TrackReferenceBox::~TrackReferenceBox() {
    for (std::vector<Box *>::size_type i = 0; i < boxes.size(); ++i) {
        delete boxes[i];
        boxes[i] = nullptr;
    }
}

Chap::Chap(BitStream &bs, const char *type, uint32_t boxSize)
        : Box(bs, type, boxSize) {
    track_ids = bs.readMultiBit(32);
}
