
#include <cstring>
#include "userDataBox.h"
#include "bitStream.h"
#include "metaBox.h"
#include "unknownBox.h"

UserDataBox::UserDataBox(BitStream &bs, const char *boxType, uint32_t size)
        : Box(bs, boxType, size, true) {
    while (offset < size) {
        uint32_t boxSize = bs.readMultiBit(32);
        offset += boxSize;
        char boxTypeName[5] = {0};
        bs.getString(boxTypeName, 4);
        parseBox(bs, boxTypeName, boxSize);
    }
}

int UserDataBox::parseBox(BitStream &bs, const char *boxType, uint32_t boxSize) {
    if (strcmp(boxType, "name") == 0) {
        boxes.push_back(new NameBox(bs, boxType, boxSize));
    } else if (strcmp(boxType, "meta") == 0) {
        boxes.push_back(new MetaBox(bs, boxType, boxSize));
    } else {
        boxes.push_back(new UnknownBox(bs, boxType, boxSize));
    }
    return 0;
}

std::vector<Box *> UserDataBox::getBoxes() const {
    return boxes;
}

UserDataBox::~UserDataBox() {
    for (std::vector<Box *>::size_type i = 0; i < boxes.size(); ++i) {
        delete boxes[i];
        boxes[i] = nullptr;
    }
}

NameBox::NameBox(BitStream &bs, const char *boxType, uint32_t size)
        : Box(bs, boxType, size) {
    uint32_t length = size - offset;

    char *name = new char[length + 1]();
    bs.getString(name, length);


    delete[] name;
}


