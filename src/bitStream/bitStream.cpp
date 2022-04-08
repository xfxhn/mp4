
#include <cstdint>
#include "bitStream.h"

BitStream::BitStream(uint8_t *buf, uint32_t _size) {
    start = buf;
    currentPtr = buf;
    endPtr = buf + _size - 1;
    size = _size;
    position = 0;
}

uint8_t BitStream::readBit() {
    --bitsLeft;

    uint8_t result = ((unsigned) (*currentPtr) >> bitsLeft) & 1u;

    if (bitsLeft == 0) {
        currentPtr++;
        position++;
        bitsLeft = 8;
    }
    return result;
}

uint32_t BitStream::readMultiBit(uint32_t n) {
    uint32_t result = 0;
    for (uint32_t i = 0; i < n; ++i) {
        //把前n位移到后面n位来
        //readBit()在算数表达式小于int类型，会被扩展为整型
        result = result | ((unsigned) readBit() << (n - i - 1u));
    }
    return result;
}

uint32_t BitStream::getMultiBit(uint32_t n) {
    uint32_t ret = 0;

    uint8_t *tempPtr = currentPtr;
    uint8_t tempBitsLeft = bitsLeft;
    uint32_t tempPosition = position;

    ret = readMultiBit(n);

    currentPtr = tempPtr;
    bitsLeft = tempBitsLeft;
    position = tempPosition;
    return ret;
}

