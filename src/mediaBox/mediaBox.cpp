#include <cstring>
#include "mediaBox.h"
#include "bitStream.h"
#include "mediaInformationBox.h"

MediaBox::MediaBox(BitStream &bs, const char *boxType, uint32_t size)
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

int MediaBox::parseBox(BitStream &bs, const char *boxType, uint32_t boxSize) {

    if (strcmp(boxType, "mdhd") == 0) {
        boxes.push_back(MediaHeaderBox(bs, boxType, boxSize));
    } else if (strcmp(boxType, "hdlr") == 0) {
        HandlerBox hdlr(bs, boxType, boxSize);
        memcpy(handler_type, hdlr.handler_type, 5);
        handler_type1 = hdlr.handler_type;
        boxes.push_back(hdlr);
        /*HandlerBox &val = dynamic_cast< HandlerBox & >(boxes[1]);
        const char *aaa = val.name;*/
    } else if (strcmp(boxType, "minf") == 0) {

        boxes.push_back(MediaInformationBox(bs, boxType, boxSize, handler_type));
    }

    return 0;
}

MediaHeaderBox::MediaHeaderBox(BitStream &bs, const char *boxType, uint32_t size)
        : FullBox(bs, boxType, size) {
    if (version == 1) {
        creation_time = bs.readMultiBit(64);
        modification_time = bs.readMultiBit(64);
        timescale = bs.readMultiBit(32);
        duration = bs.readMultiBit(64);
    } else {
        creation_time = bs.readMultiBit(32);
        modification_time = bs.readMultiBit(32);
        timescale = bs.readMultiBit(32);
        duration = bs.readMultiBit(32);
    }
    pad = bs.readBit();

    /*语种名称代码 ISO 639-2标准*/
    for (int i = 0; i < 3; ++i) {
        language[i] = static_cast<char>(bs.readMultiBit(5) + 0x60);
    }
    pre_defined = bs.readMultiBit(16);
}

HandlerBox::HandlerBox(BitStream &bs, const char *boxType, uint32_t size) : FullBox(bs, boxType, size) {
    /*预留*/
    pre_defined = bs.readMultiBit(32);
    /* 4个字节，表明是 video track、audio track 还是 hint track还是其他track*/
    bs.getString(handler_type, 4);
    /*保留*/
    bs.readMultiBit(32);
    bs.readMultiBit(32);
    bs.readMultiBit(32);

    const uint32_t len = size - 20 - 4 - 8;
    name = new char[len + 1]();

    bs.getString(name, len);

}

HandlerBox::~HandlerBox() {
    if (name) {
        delete[] name;
        name = nullptr;
    }
}
