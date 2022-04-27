
#ifndef MP4DECODER_AUDIOSAMPLEENTRY_H
#define MP4DECODER_AUDIOSAMPLEENTRY_H

#include <vector>
#include "sampleEntry.h"

class esdsConfigurationBox : public FullBox {
private:
    /*ES_DescrTag*/
    /*uint8_t ES_DescrTag;*/
    uint16_t ES_ID{};
    bool streamDependenceFlag{};
    bool URL_Flag{};
    bool OCRstreamFlag{};
    uint8_t streamPriority{};


    /*DecoderConfigDescrTag*/
    /*  uint8_t DecoderConfigDescrTag;*/
    uint8_t objectTypeIndication{};
    uint8_t streamType{};
    uint8_t upStream{};
    uint32_t bufferSizeDB{};
    uint32_t maxBitrate{};
    uint32_t avgBitrate{};


    /*uint8_t DecSpecificInfoTag;*/
    uint8_t audioObjectType{};
    uint8_t samplingFrequencyIndex{};
    uint32_t samplingFrequency{};
    uint8_t channelConfiguration{};
    uint8_t extensionAudioObjectType{};
    uint8_t extensionSamplingFrequencyIndex{};
    uint32_t extensionSamplingFrequency{};
    uint8_t extensionChannelConfiguration{};

    bool frameLengthFlag{false};
    bool dependsOnCoreCoder{false};
    bool extensionFlag{false};


    /*SLConfigDescrTag*/
    uint8_t predefined{};
private:
    int parseDescriptor(BitStream &bs, uint8_t tag);

    int ES_Descriptor(BitStream &bs);

    int DecoderConfigDescriptor(BitStream &bs);

    int DecoderSpecificInfo(BitStream &bs);

    int SLConfigDescriptor(BitStream &bs);

public:
    esdsConfigurationBox(BitStream &bs, const char *codingname, uint32_t size);

    static uint8_t GetAudioObjectType(BitStream &bs);

    int GASpecificConfig(BitStream &bs, uint8_t &bitSize);
};

class AudioSampleEntry : public SampleEntry {
private:
    std::vector<Box> boxes;
    uint16_t channelcount{2};
    uint16_t samplesize{16};
    uint32_t samplerate;
public:
    AudioSampleEntry(BitStream &bs, const char *codingname, uint32_t size);

    int parseBox(BitStream &bs, const char *boxType, uint32_t boxSize);

};

#endif //MP4DECODER_AUDIOSAMPLEENTRY_H
