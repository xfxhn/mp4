#include <cstring>
#include "mediaDataBox.h"
#include "bitStream.h"

MediaDataBox::MediaDataBox(BitStream &bs, const char *boxType, uint32_t size)
        : Box(bs, boxType, size) {

    data = new uint8_t[size]();
    memcpy(data, bs.currentPtr, size);
}

MediaDataBox::~MediaDataBox() {
    if (data) {
        delete[] data;
        data = nullptr;
    }
}

