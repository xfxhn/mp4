
#ifndef MP4DECODER_AUDIOSAMPLEENTRY_H
#define MP4DECODER_AUDIOSAMPLEENTRY_H

#include "sampleEntry.h"

class esdsConfigurationBox : public FullBox {
private:
    uint8_t ES_DescrTag;
    uint8_t ESSize;
    uint16_t ESId;
    uint8_t ESFlag;


    uint8_t DecoderConfigDescrTag;

    uint8_t DCDSize;
    uint8_t objectTypeIndication;
    uint8_t streamType;
    uint8_t upStream;
    uint32_t bufferSizeDB;
    uint32_t maxBitrate;
    uint32_t avgBitrate;


    uint8_t DecSpecificInfoTag;
    uint8_t DSDSize;
    uint8_t audioObjectType;
    uint8_t samplingFrequencyIndex;
    uint32_t samplingFrequency;
    uint8_t channelConfiguration;
    uint8_t extensionAudioObjectType;
    uint8_t extensionSamplingFrequencyIndex;
    uint32_t extensionSamplingFrequency;
    uint8_t extensionChannelConfiguration;

    bool frameLengthFlag;
    bool dependsOnCoreCoder;
    bool extensionFlag;
public:
    esdsConfigurationBox(BitStream &bs, const char *codingname, uint32_t size);

    static uint8_t GetAudioObjectType(BitStream &bs);

    int GASpecificConfig(BitStream &bs);
};

class AudioSampleEntry : public SampleEntry {
private:
    uint16_t channelcount{2};
    uint16_t samplesize{16};
    uint32_t samplerate;
public:
    AudioSampleEntry(BitStream &bs, const char *codingname, uint32_t size);

    int parseBox(BitStream &bs, const char *boxType, uint32_t boxSize);

};

#endif //MP4DECODER_AUDIOSAMPLEENTRY_H
