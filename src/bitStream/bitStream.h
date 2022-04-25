
#ifndef AACDECODER_BITSTREAM_H
#define AACDECODER_BITSTREAM_H

#include "cstdint"

class BitStream {
private:
    //指向开始的位置
    uint8_t *start = nullptr;
    // buffer 的长度（单位 Byte）
    uint32_t size = 0;

    uint8_t *endPtr = nullptr;

    // 当前读取到了字节中的第几位
    uint8_t bitsLeft = 8;

public:
    // 读取到第几字节
    uint32_t position;

    // 当前读取到了哪个字节的指针
    uint8_t *currentPtr = nullptr;

    BitStream(uint8_t *buf, uint32_t _size);

    //读取1bit
    uint8_t readBit();

    //读取n个bit
    uint64_t readMultiBit(uint32_t n);

    int getString(char str[], uint32_t n);

    //获取n个bit
    uint32_t getMultiBit(uint32_t n);
};

#endif //AACDECODER_BITSTREAM_H
