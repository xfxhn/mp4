
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

class FullBox : public Box {
private:
    uint8_t version;
    uint8_t flags;
public:
    FullBox(BitStream &bs, const char *boxtype, uint32_t size);
};

#endif //MP4DECODER_BOX_H
