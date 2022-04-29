
#include <iostream>

#include <cstring>
#include "decoder.h"
#include "bitStream.h"
#include "fileTypeBox.h"
#include "movieBox.h"
#include "mediaDataBox.h"
#include "handlerBox.h"
#include "sampleTableBox.h"

// 每次读取的字节数，1024kb
#define BYTES_READ_PER_TIME 1024 * 1024

#define min(a, b) ( (a) < (b) ? (a) : (b) )

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

    /*file.seekg(8900, std::ios::beg);

    uint8_t *aaa = new uint8_t[10000]();

    file.read(reinterpret_cast<char *>(aaa), 10000);
    BitStream bs(aaa, 10000);

    uint32_t naluLength = bs.readMultiBit(32);
    int www = 1;
    return 1;*/
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

//    MovieBox &box = dynamic_cast< MovieBox & >(boxes[1]);
    test(boxes);
    parseHavc();

    return 0;
}

int Decoder::getBoxInfo(boxInfo &info, BitStream &bs) {
    uint32_t size = bs.readMultiBit(32);

    char type[5] = {0};
    bs.getString(type, 4);


    if (strcmp(type, "ftyp") == 0) {
        info.size = size;
        info.type = "ftyp";

//        FileTypeBox ftyp(bs, "ftyp", size);
        boxes.push_back(new FileTypeBox(bs, "ftyp", size));
    } else if (strcmp(type, "moov") == 0) {
        info.size = size;
        info.type = "moov";

//        MovieBox moov(bs, "moov", size);
        boxes.push_back(new MovieBox(bs, "moov", size));

    } else if (strcmp(type, "mdat") == 0) {
        info.size = size;
        info.type = "mdat";

//        MediaDataBox mdat(bs, "mdat", size);
        boxes.push_back(new MediaDataBox(bs, "mdat", size));
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

            /*如果读不满 fillByteSize 大小代表读到尾部了，size是实际读取了多大*/
            if (size != fillByteSize) {
                isEof = false;
            }
            readFileSize += size;
        }
        fillByteSize = 0;
    }
    return 0;
}

int Decoder::test(std::vector<Box *> &list, const char *handler_type) {
    for (std::vector<Box>::size_type i = 0; i < list.size(); ++i) {

        Box *box = list[i];
        const char *type = box->type;

        std::cout << type << std::endl;

        if (strcmp(type, "hdlr") == 0) {
            handler_type = dynamic_cast<HandlerBox *>(box)->handler_type;
        }
        if (strcmp(handler_type, "vide") == 0) { //视频track
            if (strcmp(type, "stsc") == 0) {
                stsc = dynamic_cast<SampleToChunkBox *>(box);

                int b = 1;
            }

            if (strcmp(type, "stco") == 0) {
                stco = dynamic_cast<ChunkOffsetBox *>(box);
                int b = 1;
            }

            if (strcmp(type, "stsz") == 0) {
                stsz = dynamic_cast<SampleSizeBox *>(box);
                int b = 1;
            }

        } else if (strcmp(handler_type, "soun") == 0) { //音频track

        }
        if (box->containerBoxFlag) {
            std::vector<Box *> boxList = box->getBoxes();
            test(boxList, handler_type);

            /*if (strcmp(type, "moov") == 0) {
                MovieBox *box = dynamic_cast< MovieBox * >(list[i]);
                test(box->boxes);
            }*/
        }
    }

    return 0;
}

Decoder::~Decoder() {
    for (std::vector<Box *>::size_type i = 0; i < boxes.size(); ++i) {
        delete boxes[i];
        boxes[i] = nullptr;
    }
}

int Decoder::parseHavc() {
    uint32_t index = 0;
    const uint32_t chunkSize = stco->entry_count;

    const uint32_t first_chunk = stsc->first_chunk[0];

    for (int i = 0; i < stsc->entry_count; ++i) {

        for (index = 0; index < stsc->first_chunk[i]; ++index) {
            int a = 1;
        }
        index = stsc->first_chunk[i];
    }

    /*for (uint32_t i = 0; i < chunkSize; ++i) {

    }
*/
    int a = 1;

    return 0;
}
