
#ifndef MP4_TRACKBOX_H
#define MP4_TRACKBOX_H

#include <vector>
#include "box.h"

class TrackHeaderBox : public FullBox {
private:
    uint64_t creation_time;
    uint64_t modification_time;
    uint32_t track_ID;
    uint64_t duration;
    uint16_t layer;
    uint16_t alternate_group;
    float volume;
    uint32_t matrix[9]{0};
    float width;
    float height;
public:
    TrackHeaderBox(BitStream &bs, const char *boxType, uint32_t size);
};


class TrackBox : public Box {
public:
    std::vector<Box *> boxes;

    TrackBox(BitStream &bs, const char *boxType, uint32_t size);

    std::vector<Box *> getBoxes() const override;

    int parseBox(BitStream &bs, const char *boxType, uint32_t boxSize);

    ~TrackBox() override;

};

#endif //MP4DECODER_TRACKBOX_H
