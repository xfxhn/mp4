
#include <cstring>
#include "userDataBox.h"
#include "bitStream.h"
#include "metaBox.h"

UserDataBox::UserDataBox(BitStream &bs, const char *boxType, uint32_t size)
        : Box(bs, boxType, size) {
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
        NameBox name(bs, boxType, boxSize);
        boxes.push_back(name);
    } else if (strcmp(boxType, "meta") == 0) {
        MetaBox meta(bs, boxType, boxSize);
        boxes.push_back(meta);
    }
    return 0;
}

NameBox::NameBox(BitStream &bs, const char *boxType, uint32_t size)
        : Box(bs, boxType, size) {
    uint32_t length = size - offset;

    char *name = new char[length + 1]();
    bs.getString(name, length);


    delete[] name;
}


