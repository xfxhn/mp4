#ifndef MP4DECODER_SAMPLETABLEBOX_H
#define MP4DECODER_SAMPLETABLEBOX_H

#include <vector>
#include "box.h"


class SampleDescriptionBox : public FullBox {
private:
    std::vector<Box> boxes;
    uint32_t entry_count;
public:
    SampleDescriptionBox(BitStream &bs, const char *boxType, uint32_t size, const char *handler_type);
};

class SampleTableBox : public Box {
private:
    std::vector<Box> boxes;

    const char *handler_type_;
public:
    SampleTableBox(BitStream &bs, const char *boxType, uint32_t size, const char *handler_type);

    int parseBox(BitStream &bs, const char *boxType, uint32_t boxSize);
};

#endif //MP4DECODER_SAMPLETABLEBOX_H
