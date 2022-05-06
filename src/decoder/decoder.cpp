
#include <iostream>

#include <cstring>
#include <iomanip>
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

    /*file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    uint32_t offset = 0;

    while (offset < fileSize) {

        file.read(reinterpret_cast<char *>(buffer), 4);
    }*/


    buffer = new uint8_t[BYTES_READ_PER_TIME]();

    file.read(reinterpret_cast<char *>(buffer), BYTES_READ_PER_TIME);
    readFileSize = file.gcount();

    decode();
    return 0;
}

int Decoder::decode() {

//    uint32_t offset = 0;


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

        boxes.push_back(new MovieBox(bs, "moov", size));

    } else if (strcmp(type, "mdat") == 0) {
        info.size = size;
        info.type = "mdat";

        mdat = new MediaDataBox(bs, "mdat", size);
        boxes.push_back(mdat);
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

int Decoder::test(const std::vector<Box *> &list, const char *handler_type, int spacing) {
    for (std::vector<Box>::size_type i = 0; i < list.size(); ++i) {

        Box *box = list[i];
        const char *type = box->type;
        std::cout.width(spacing);
        std::cout << type << std::endl;

        if (strcmp(type, "hdlr") == 0) {
            handler_type = dynamic_cast<HandlerBox *>(box)->handler_type;
        }
        if (strcmp(handler_type, "vide") == 0) { //视频track
            if (strcmp(type, "stsc") == 0) {
                stsc = dynamic_cast<SampleToChunkBox *>(box);
            }

            if (strcmp(type, "stco") == 0) {
                stco = dynamic_cast<ChunkOffsetBox *>(box);
            }

            if (strcmp(type, "stsz") == 0) {
                stsz = dynamic_cast<SampleSizeBox *>(box);
            }

            if (strcmp(type, "stsd") == 0) {
                videStsd = dynamic_cast<SampleDescriptionBox *>(box);
            }

        } else if (strcmp(handler_type, "soun") == 0) { //音频track

        }
        if (box->containerBoxFlag) {
            std::vector<Box *> boxList = box->getBoxes();
            test(boxList, handler_type, spacing + 4);
        }
    }

    return 0;
}

int Decoder::parseHavc() {
    uint8_t startCode[4] = {0, 0, 0, 1};
    std::ofstream fout("output/test.h264", std::ios::binary | std::ios::out | std::ios::trunc);
    if (!fout.is_open()) {
        std::cout << "打开文件失败" << std::endl;
        /*fout.write(reinterpret_cast<const char *>(startCode), 5);*/
    }

    uint32_t chunkIndex = 0;
    uint32_t sampleIndex = 0;
    for (int i = 0; i < stsc->entry_count; ++i) {
        uint32_t currVal = stsc->first_chunk[i];
        uint32_t nextVal = stsc->first_chunk[i + 1];
        if (i + 1 == stsc->entry_count) {
            nextVal = stsc->first_chunk[i] + 1;
        }
        for (uint32_t j = currVal; j < nextVal; ++j) {
            std::cout << stsc->samples_per_chunk[i] << std::endl;

            /*每个chunk对应的sps pps等一些解码信息*/
            VisualSampleEntry *vide = dynamic_cast<VisualSampleEntry *>(videStsd->getBoxes()[stsc->sample_description_index[i]]);
            std::vector<Box *> boxList = vide->getBoxes();

            AVCConfigurationBox *avcC = nullptr;
            for (int l = 0; l < boxList.size(); ++l) {
                if (strcmp(boxList[l]->type, "avcC") == 0) {
                    avcC = dynamic_cast<AVCConfigurationBox *>(boxList[l]);
                }
            }

            /*sps*/
            fout.write(reinterpret_cast<const char *>(startCode), 4);
            fout.write(reinterpret_cast<const char *>(avcC->AVCConfig.sequenceParameterSetNALUnit[0]),
                       avcC->AVCConfig.sequenceParameterSetLength[0]);
            /*pps*/
            fout.write(reinterpret_cast<const char *>(startCode), 4);
            fout.write(reinterpret_cast<const char *>(avcC->AVCConfig.pictureParameterSetNALUnit[0]),
                       avcC->AVCConfig.pictureParameterSetLength[0]);

            uint32_t chunkOffset = stco->chunk_offsets[chunkIndex] - stco->chunk_offsets[0];
            for (uint32_t k = 0; k < stsc->samples_per_chunk[i]; ++k) {

                uint32_t sampleSize = stsz->entry_size_list[sampleIndex];

                BitStream bs(mdat->data + chunkOffset, sampleSize);
                uint32_t offset = 0;
                while (offset < sampleSize) {
                    uint32_t naluSize = bs.readMultiBit(32);
                    offset += 4;
                    offset += naluSize;
                    fout.write(reinterpret_cast<const char *>(startCode), 4);
                    fout.write(reinterpret_cast<const char *>(bs.currentPtr), naluSize);
                    bs.setBytePtr(naluSize);
                }
                fout.close();
                /*fout.write(reinterpret_cast<const char *>(startCode), 4);

                fout.write(reinterpret_cast<const char *>(mdat->data), sampleSize);
                fout.close();*/
                ++sampleIndex;
            }
            ++chunkIndex;
        }
    }
    fout.close();
    std::cout << chunkIndex << std::endl;
    std::cout << sampleIndex << std::endl;
    int a = 1;

    return 0;
}

Decoder::~Decoder() {
    for (std::vector<Box *>::size_type i = 0; i < boxes.size(); ++i) {
        delete boxes[i];
        boxes[i] = nullptr;
    }
}