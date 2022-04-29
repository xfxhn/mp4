#include <cstring>
#include "mediaBox.h"
#include "bitStream.h"
#include "handlerBox.h"
#include "mediaInformationBox.h"
#include "unknownBox.h"

MediaBox::MediaBox(BitStream &bs, const char *boxType, uint32_t size)
        : Box(bs, boxType, size, true) {

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
        boxes.push_back(new MediaHeaderBox(bs, boxType, boxSize));
    } else if (strcmp(boxType, "hdlr") == 0) {
        HandlerBox *hdlr = new HandlerBox(bs, boxType, boxSize);
        strcpy(handler_type, hdlr->handler_type);
        boxes.push_back(hdlr);
        /*HandlerBox &val = dynamic_cast< HandlerBox & >(boxes[1]);*/
    } else if (strcmp(boxType, "minf") == 0) {
        boxes.push_back(new MediaInformationBox(bs, boxType, boxSize, handler_type));
    } else {
        boxes.push_back(new UnknownBox(bs, boxType, boxSize));
    }

    return 0;
}

std::vector<Box *> MediaBox::getBoxes() const {
    return boxes;
}

MediaBox::~MediaBox() {
    for (std::vector<Box *>::size_type i = 0; i < boxes.size(); ++i) {
        delete boxes[i];
        boxes[i] = nullptr;
    }
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

