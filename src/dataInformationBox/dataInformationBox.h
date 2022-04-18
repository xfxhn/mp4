
#ifndef MP4DECODER_DATAINFORMATIONBOX_H
#define MP4DECODER_DATAINFORMATIONBOX_H

#include <vector>
#include "box.h"

class DataInformationBox : public Box {
public:
    std::vector<Box> boxes;

    DataInformationBox(BitStream &bs, const char *boxType, uint32_t size);

    int parseBox(BitStream &bs, const char *boxType, uint32_t boxSize);
};

#endif //MP4DECODER_DATAINFORMATIONBOX_H
