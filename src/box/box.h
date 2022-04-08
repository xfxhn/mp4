
#ifndef MP4DECODER_BOX_H
#define MP4DECODER_BOX_H

#include <cstdint>

class Box {
private:
    uint32_t size;
    uint32_t type;
public:
    Box(uint32_t boxtype, uint32_t extended_type);
};

#endif //MP4DECODER_BOX_H
