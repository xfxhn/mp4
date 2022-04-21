
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
    uint16_t sequenceParameterSetLength[32]{0};
    uint8_t *sequenceParameterSetNALUnit[32]{nullptr};

    uint8_t numOfPictureParameterSets;
    /*pic_parameter_set_id的值应该0到255的范围内（包括0 和255）。*/
    uint16_t pictureParameterSetLength[256]{0};
    uint8_t *pictureParameterSetNALUnit[256]{nullptr};


    uint8_t chroma_format{1};
    uint8_t bit_depth_luma_minus8{0};
    uint8_t bit_depth_chroma_minus8{0};


    uint8_t numOfSequenceParameterSetExt{0};
    uint16_t sequenceParameterSetExtLength[256]{0};
    uint8_t *sequenceParameterSetExtNALUnit[256]{nullptr};

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
