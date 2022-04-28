#ifndef MP4_MEDIADATABOX_H
#define MP4_MEDIADATABOX_H

#include "box.h"

class MediaDataBox : public Box {
private:
    uint8_t *data{nullptr};
public:
    MediaDataBox(BitStream &bs, const char *boxType, uint32_t size);

    ~MediaDataBox() override;
};

#endif //MP4_MEDIADATABOX_H
