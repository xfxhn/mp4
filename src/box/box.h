
#ifndef MP4DECODER_BOX_H
#define MP4DECODER_BOX_H

#include <cstdint>

class BitStream;

class Box {
private:
    uint32_t size;
    const char *type;
public:
    Box(BitStream &bs, const char *boxtype, uint32_t size);

    virtual  ~Box() = default;
};

#endif //MP4DECODER_BOX_H
