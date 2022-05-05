#include "mediaDataBox.h"

MediaDataBox::MediaDataBox(BitStream &bs, const char *boxType, uint32_t size)
        : Box(bs, boxType, size) {

    data = new uint8_t[size]();
}

MediaDataBox::~MediaDataBox() {
    if (data) {
        delete[] data;
        data = nullptr;
    }
}

