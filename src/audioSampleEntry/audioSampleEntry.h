
#ifndef MP4DECODER_AUDIOSAMPLEENTRY_H
#define MP4DECODER_AUDIOSAMPLEENTRY_H

#include "sampleEntry.h"


class AudioSampleEntry : public SampleEntry {
private:
    uint16_t channelcount{2};
    uint16_t samplesize{16};
    uint16_t pre_defined{16};
    uint32_t samplerate;
public:
    AudioSampleEntry(BitStream &bs, const char *codingname, uint32_t size);
};

#endif //MP4DECODER_AUDIOSAMPLEENTRY_H
