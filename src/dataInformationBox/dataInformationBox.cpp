#include <cstring>
#include "dataInformationBox.h"
#include "bitStream.h"
#include "unknownBox.h"


DataInformationBox::DataInformationBox(BitStream &bs, const char *boxType, uint32_t size)
        : Box(bs, boxType, size, true) {

    while (offset < size) {
        uint32_t boxSize = bs.readMultiBit(32);
        offset += boxSize;
        char boxTypeName[5] = {0};
        bs.getString(boxTypeName, 4);
        parseBox(bs, boxTypeName, boxSize);
    }
}

int DataInformationBox::parseBox(BitStream &bs, const char *boxType, uint32_t boxSize) {

    if (strcmp(boxType, "url ") == 0) {
        boxes.push_back(new DataEntryUrlBox(bs, "url ", boxSize));
    } else if (strcmp(boxType, "urn ") == 0) {
        boxes.push_back(new DataEntryUrnBox(bs, "urn ", boxSize));
    } else if (strcmp(boxType, "dref") == 0) {
        boxes.push_back(new DataReferenceBox(bs, "dref", boxSize));
    }
    return 0;
}

std::vector<Box *> DataInformationBox::getBoxes() const {
    return boxes;
}

DataInformationBox::~DataInformationBox() {
    for (std::vector<Box *>::size_type i = 0; i < boxes.size(); ++i) {
        delete boxes[i];
        boxes[i] = nullptr;
    }
}

DataEntryUrlBox::DataEntryUrlBox(BitStream &bs, const char *boxType, uint32_t size)
        : FullBox(bs, boxType, size) {

    /*当“url”或“urn”的box flag为1时，字符串均为空。*/
    // flag 为 1，表示媒体数据包含在了当前movie文件里
    if (flags != 1) {
        const uint32_t len = size - offset;
        location = new char[len + 1]();
        bs.getString(location, len);
    }
}

DataEntryUrlBox::~DataEntryUrlBox() {
    if (location) {
        delete[] location;
        location = nullptr;
    }
}

DataEntryUrnBox::DataEntryUrnBox(BitStream &bs, const char *boxType, uint32_t size)
        : FullBox(bs, boxType, size) {

    /*每个都是一个使用UTF-8字符的以空结束的字符串*/
    if (flags != 1) {
        const uint32_t len = size - 4 - 8;
        int i = 0;
        while (bs.getMultiBit(8) != 0) {
            i++;
        }
        name = new char[i + 1]();
        bs.getString(name, len);
        if (len - i > 0) {
            location = new char[len - i + 1]();
            bs.getString(location, len - i);
        }

    }

}

DataEntryUrnBox::~DataEntryUrnBox() {
    if (name) {
        delete[] name;
        name = nullptr;
    }
    if (location) {
        delete[] location;
        location = nullptr;
    }
}

DataReferenceBox::DataReferenceBox(BitStream &bs, const char *boxType, uint32_t size)
        : FullBox(bs, boxType, size, true) {
    entry_count = bs.readMultiBit(32);
    offset += 4;
    while (offset < size) {
        uint32_t boxSize = bs.readMultiBit(32);
        offset += boxSize;
        char boxTypeName[5] = {0};
        bs.getString(boxTypeName, 4);
        parseBox(bs, boxTypeName, boxSize);
    }
}

int DataReferenceBox::parseBox(BitStream &bs, const char *boxType, uint32_t boxSize) {

    if (strcmp(boxType, "url ") == 0) {
        boxes.push_back(new DataEntryUrlBox(bs, boxType, boxSize));
    } else if (strcmp(boxType, "urn ") == 0) {
        boxes.push_back(new DataEntryUrnBox(bs, boxType, boxSize));
    } else {
        boxes.push_back(new UnknownBox(bs, boxType, boxSize));
    }
    return 0;
}

std::vector<Box *> DataReferenceBox::getBoxes() const {
    return boxes;
}
