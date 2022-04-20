
#ifndef MP4DECODER_VISUALSAMPLEENTRY_H
#define MP4DECODER_VISUALSAMPLEENTRY_H

#include "box.h"

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
public:
    VisualSampleEntry(BitStream &bs, const char *codingname, uint32_t size);
};

#endif //MP4DECODER_VISUALSAMPLEENTRY_H
