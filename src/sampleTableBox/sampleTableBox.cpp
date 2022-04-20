#include <cstring>
#include "sampleTableBox.h"
#include "bitStream.h"
#include "visualSampleEntry.h"

SampleTableBox::SampleTableBox(BitStream &bs, const char *boxType, uint32_t size, const char *handler_type)
        : Box(bs, boxType, size), handler_type_(handler_type) {
    /*type 4 size 4*/
    uint32_t offset = 8;

    while (offset < size) {
        uint32_t boxSize = bs.readMultiBit(32);
        offset += boxSize;
        char boxTypeName[5] = {0};
        bs.getString(boxTypeName, 4);
        parseBox(bs, boxTypeName, boxSize);
    }
}

int SampleTableBox::parseBox(BitStream &bs, const char *boxType, uint32_t boxSize) {

    if (strcmp(boxType, "stsd") == 0) {
        SampleDescriptionBox stsd(bs, boxType, boxSize, handler_type_);
        boxes.push_back(stsd);
    }
    return 0;
}

/*stsd*/
SampleDescriptionBox::SampleDescriptionBox(BitStream &bs, const char *boxType, uint32_t size, const char *handler_type)
        : FullBox(bs, boxType, size) {


    int i;
    entry_count = bs.readMultiBit(32);

    /*type 4 size 4 version 1 flags 3 entry_count 4*/
    uint32_t offset = 16;
    while (offset < size) {
        uint32_t boxSize = bs.readMultiBit(32);
        offset += boxSize;
        char boxTypeName[5] = {0};
        bs.getString(boxTypeName, 4);

        for (i = 1; i <= entry_count; ++i) {
            if (strcmp(handler_type, "soun") == 0) {// for audio tracks

            } else if (strcmp(handler_type, "vide") == 0) {// for video tracks
                VisualSampleEntry vide(bs, boxTypeName, boxSize);
                boxes.push_back(vide);
            } else if (strcmp(handler_type, "hint") == 0) {// Hint track

            } else if (strcmp(handler_type, "meta") == 0) {// Metadata track

            }
        }
        int aa = 1;
        // parseBox(bs, boxTypeName, boxSize);
    }


}


