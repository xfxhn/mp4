
#ifndef MP4DECODER_DECODER_H
#define MP4DECODER_DECODER_H

#include <fstream>

#include <cstdint>
#include <vector>
#include "box.h"
#include "visualSampleEntry.h"

struct boxInfo;

class BitStream;

class SampleToChunkBox;

class ChunkOffsetBox;

class SampleSizeBox;

class MediaDataBox;

class SampleDescriptionBox;

class Decoder {
private:

    std::vector<Box *> boxes;

    uint64_t fileSize{0};
    uint8_t *buffer{nullptr};
    std::ifstream file;


    /*每次循环读取的数目*/
    uint32_t readFileSize{0};
    /*每次循环需要填充的数目*/
    uint32_t fillByteSize{0};
    bool isEof{true};


    SampleToChunkBox *stsc;
    ChunkOffsetBox *stco;
    SampleSizeBox *stsz;
    MediaDataBox *mdat;
    SampleDescriptionBox *videStsd;
public:
    int init(const char *fileName);

    ~Decoder();

private:
    int decode();

    int getBoxInfo(boxInfo &info, BitStream &bs);


    int advanceBuffer(uint32_t length);

    int fillBuffer();

    int test(const std::vector<Box *> &list, const char *handler_type = "", int spacing = 4);

    int parseHavc();
};

#endif //MP4DECODER_DECODER_H
