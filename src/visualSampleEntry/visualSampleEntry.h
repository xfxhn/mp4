
#ifndef MP4DECODER_VISUALSAMPLEENTRY_H
#define MP4DECODER_VISUALSAMPLEENTRY_H

#include <vector>
#include "box.h"

class AVCDecoderConfigurationRecord {
private:

    uint8_t configurationVersion;
    uint8_t AVCProfileIndication;
    uint8_t profile_compatibility;
    uint8_t AVCLevelIndication;
    uint8_t lengthSizeMinusOne;
    uint8_t numOfSequenceParameterSets;

    /*seq_parameter_set_id在0-31 的范围内，包括0和31*/
    uint8_t *sequenceParameterSets[32];
public:
    /*防止隐式调用构造函数*/
    explicit AVCDecoderConfigurationRecord(BitStream &bs);
};

/* AVCConfig*/
class AVCConfigurationBox : public Box {
    AVCDecoderConfigurationRecord AVCConfig;
public:
    AVCConfigurationBox(BitStream &bs, const char *BoxType, uint32_t size);
};


class SampleEntry : public Box {
private:
    uint16_t data_reference_index;
public:
    SampleEntry(BitStream &bs, const char *format, uint32_t size);
};

class VisualSampleEntry : public SampleEntry {

private:
    uint16_t width;
    uint16_t height;
    double horizresolution{72};
    double vertresolution{72};
    uint16_t frame_count{0};
    char *compressorname{nullptr};
    uint16_t depth{24};

    std::vector<Box> boxes;
public:
    VisualSampleEntry(BitStream &bs, const char *codingname, uint32_t size);

    int parseBox(BitStream &bs, const char *boxType, uint32_t boxSize);
};

#endif //MP4DECODER_VISUALSAMPLEENTRY_H
