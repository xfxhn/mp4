
#ifndef MP4DECODER_DECODER_H
#define MP4DECODER_DECODER_H

#include <fstream>
#include <cstdint>
#include <vector>
#include "box.h"

struct boxInfo;

class BitStream;

class Decoder {
private:

    std::vector<Box *> boxes;


    uint8_t *buffer{nullptr};
    std::ifstream file;

    /*每次循环读取的数目*/
    uint32_t readFileSize{0};
    /*每次循环需要填充的数目*/
    uint32_t fillByteSize{0};
    bool isEof{true};
public:
    int init(const char *fileName);

    ~Decoder();

private:
    int decode();

    int getBoxInfo(boxInfo &info, BitStream &bs);


    int advanceBuffer(uint32_t length);

    int fillBuffer();

    int test(std::vector<Box *> &list);
};

#endif //MP4DECODER_DECODER_H
