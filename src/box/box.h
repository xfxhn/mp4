
#ifndef MP4DECODER_BOX_H
#define MP4DECODER_BOX_H

#include <vector>
#include <cstdint>

class BitStream;

class Box {
public:
    uint32_t offset;
    uint32_t size;
    char type[5]{0};
    char usertype[17]{0};
    bool containerBoxFlag{false};
public:
    Box(BitStream &bs, const char *boxtype, uint32_t size, bool flag = false);

    virtual std::vector<Box *> getBoxes() const;

    Box(const Box &a) = default;

    virtual  ~Box() = default;
};

class FullBox : public Box {
protected:
    /*version is an integer that specifies the version of this box */
    uint8_t version;
    uint32_t flags;
public:
    FullBox(BitStream &bs, const char *boxtype, uint32_t size, bool flag = false);

    FullBox(const FullBox &val);

    ~FullBox() override = default;
};

#endif //MP4DECODER_BOX_H
