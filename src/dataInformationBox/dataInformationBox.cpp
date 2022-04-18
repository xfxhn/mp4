//
// Created by Administrator on 2022/4/18.
//
#include <cstring>
#include "dataInformationBox.h"
#include "bitStream.h"


DataInformationBox::DataInformationBox(BitStream &bs, const char *boxType, uint32_t size)
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

int DataInformationBox::parseBox(BitStream &bs, const char *boxType, uint32_t boxSize) {

    if (strcmp(boxType, "url ") == 0) {
        boxes.push_back(DataEntryUrlBox(bs, boxType, boxSize));
    } else if (strcmp(boxType, "urn ") == 0) {
        boxes.push_back(DataEntryUrnBox(bs, boxType, boxSize));
    } else if (strcmp(boxType, "dref") == 0) {
        boxes.push_back(DataReferenceBox(bs, "dref", boxSize));
    }
    return 0;
}

DataEntryUrlBox::DataEntryUrlBox(BitStream &bs, const char *boxType, uint32_t size)
        : FullBox(bs, boxType, size) {
    const uint32_t len = size - 4 - 8;
    location = new char[len + 1]();

    bs.getString(location, len);
}

DataEntryUrlBox::~DataEntryUrlBox() {
    if (location) {
        delete[] location;
        location = nullptr;
    }
}

DataEntryUrnBox::DataEntryUrnBox(BitStream &bs, const char *boxType, uint32_t size)
        : FullBox(bs, boxType, size) {
    const uint32_t len = size - 4 - 8;
    location = new char[len + 1]();

    bs.getString(location, len);
}

DataEntryUrnBox::~DataEntryUrnBox() {
    if (location) {
        delete[] location;
        location = nullptr;
    }
}

DataReferenceBox::DataReferenceBox(BitStream &bs, const char *boxType, uint32_t size)
        : FullBox(bs, boxType, size) {
    entry_count = bs.readMultiBit(32);

    uint32_t offset = 0;
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
        boxes.push_back(DataEntryUrlBox(bs, boxType, boxSize));
    } else if (strcmp(boxType, "urn ") == 0) {
        boxes.push_back(DataEntryUrnBox(bs, boxType, boxSize));
    }
    return 0;
}
