
#ifndef MP4DECODER_MEDIAINFORMATIONBOX_H
#define MP4DECODER_MEDIAINFORMATIONBOX_H

#include <vector>
#include "box.h"

class MediaInformationBox : public Box {
public:
    std::vector<Box> boxes;

    MediaInformationBox(BitStream &bs, const char *boxType, uint32_t size);

    int parseBox(BitStream &bs, const char *boxType, uint32_t boxSize);
};

#endif //MP4DECODER_MEDIAINFORMATIONBOX_H
