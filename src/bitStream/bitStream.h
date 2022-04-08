//
// Created by Administrator on 2022/3/17.
//

#ifndef AACDECODER_BITSTREAM_H
#define AACDECODER_BITSTREAM_H

class BitStream {
private:
    //指向开始的位置
    uint8_t *start = nullptr;
    // buffer 的长度（单位 Byte）
    uint32_t size = 0;
    // 当前读取到了哪个字节
    uint8_t *currentPtr = nullptr;
    uint8_t *endPtr = nullptr;

    // 当前读取到了字节中的第几位
    uint8_t bitsLeft = 8;
    // 读取到第几字节
    uint32_t position;
public:
    BitStream(uint8_t *buf, uint32_t _size);

    //读取1bit
    uint8_t readBit();

    //读取n个bit
    uint32_t readMultiBit(uint32_t n);

    //获取n个bit
    uint32_t getMultiBit(uint32_t n);
};

#endif //AACDECODER_BITSTREAM_H
