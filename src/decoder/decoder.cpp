
#include <iostream>

#include <cstring>
#include "decoder.h"
#include "bitStream.h"
#include "FileTypeBox.h"
#include "movieBox.h"

// 每次读取的字节数，256kb
#define BYTES_READ_PER_TIME 1024 * 1024

#define min(a, b) ( (a) < (b) ? (a) : (b) )

enum boxType {
    ftyp
};
struct boxInfo {
    uint32_t size;
    const char *type;
    uint8_t *buffer;
};


int Decoder::init(const char *fileName) {


    file.open(fileName, std::ios::binary);

    if (!file.is_open()) {
        std::cout << "读取文件失败" << std::endl;
        return -1;
    }
    buffer = new uint8_t[BYTES_READ_PER_TIME]();

    file.read(reinterpret_cast<char *>(buffer), BYTES_READ_PER_TIME);
    readFileSize = file.gcount();

    decode();
    return 0;
}

int Decoder::decode() {


    while (true) {
        fillBuffer();
        if (readFileSize > 0) {
            BitStream bs(buffer, readFileSize);


            boxInfo info;
            getBoxInfo(info, bs);

            if (info.size == 0) {
                break;
            }
            advanceBuffer(info.size);
        } else {
            fillByteSize = 0;
            break;
        }

    }
    return 0;
}

int Decoder::getBoxInfo(boxInfo &info, BitStream &bs) {
    uint32_t size = bs.readMultiBit(32);

    char type[5] = {0};
    bs.getString(type, 4);


    if (strcmp(type, "ftyp") == 0) {
        info.size = size;
        info.type = "ftyp";

        FileTypeBox ftyp(bs, "ftyp", size);
        boxes.push_back(ftyp);
    } else if (strcmp(type, "moov") == 0) {
        info.size = size;
        info.type = "moov";

        MovieBox moov(bs, "moov", size);
        boxes.push_back(moov);

    } else if (strcmp(type, "mdat") == 0) {
        info.size = size;
        info.type = "mdat";

        bs.readMultiBit(32);
    }

    return 0;
}

int Decoder::advanceBuffer(uint32_t length) {
    if (length > 0 && readFileSize > 0) {
        uint32_t size = min(length, readFileSize);
        fillByteSize += size;
        readFileSize -= size;
    }
    return 0;
}

int Decoder::fillBuffer() {
    if (fillByteSize > 0) {
        if (readFileSize) {
            //void *memmove(void *dest, const void *src, unsigned int count);
            //由src所指内存区域复制count个字节到dest所指内存区域。

            /*把后面的未读取的移动到前面来*/
            memmove(buffer, (buffer + fillByteSize), readFileSize);
        }

        if (isEof) {
            /*填补后面已经读取的fillByteSize个字节*/
            file.read(reinterpret_cast<char *>(buffer + readFileSize), fillByteSize);
            uint32_t size = file.gcount();

            /*如果读不满 fillByteSize 大小代表读到尾部了size是实际读取了多大*/
            if (size != fillByteSize) {
                isEof = false;
            }
            readFileSize += size;
        }
        fillByteSize = 0;
    }
    return 0;
}
