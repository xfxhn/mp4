
#ifndef MP4_XIAOFENG_H
#define MP4_XIAOFENG_H

#include "box.h"

class SampleEntry : public Box {
private:
    uint16_t data_reference_index;
public:
    SampleEntry(BitStream &bs, const char *format, uint32_t size);
};

#endif //MP4DECODER_XIAOFENG_H
