#include "handlerBox.h"
#include "bitStream.h"

HandlerBox::HandlerBox(BitStream &bs, const char *boxType, uint32_t size) : FullBox(bs, boxType, size) {
    /*预留*/
    bs.readMultiBit(32);
    offset += 4;
    /* 4个字节，表明是 video track、audio track 还是 hint track还是其他track*/
    bs.getString(handler_type, 4);
    offset += 4;
    /*保留*/
    bs.readMultiBit(32);
    bs.readMultiBit(32);
    bs.readMultiBit(32);
    offset += 12;
    const uint32_t len = size - offset;
    name = new char[len + 1]();

    bs.getString(name, len);

}

HandlerBox::~HandlerBox() {
    if (name) {
        delete[] name;
        name = nullptr;
    }
}

