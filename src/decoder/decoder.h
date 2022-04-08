
#ifndef MP4DECODER_DECODER_H
#define MP4DECODER_DECODER_H

#include <iostream>
#include <fstream>
#include "decoder.h"
#include "bitStream.h"

// 每次读取的字节数，256kb
#define BYTES_READ_PER_TIME 256 * 1024;


int Decoder::initDecoder(const char *fileName) {
    std::ifstream file(fileName, std::ios::binary);

    if (!file.is_open()) {
        std::cout << "读取文件失败" << std::endl;
        return -1;
    }


    return 0;
}

#endif //MP4DECODER_DECODER_H
