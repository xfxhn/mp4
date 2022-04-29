
#ifndef MP4DECODER_TRACKREFERENCEBOX_H
#define MP4DECODER_TRACKREFERENCEBOX_H

#include "box.h"

class Chap : public Box {
private:
    uint32_t track_ids;
public:
    Chap(BitStream &bs, const char *type, uint32_t boxSize);
};

class TrackReferenceBox : public Box {
public:
    std::vector<Box *> boxes;

    TrackReferenceBox(BitStream &bs, const char *format, uint32_t size);

    std::vector<Box *> getBoxes() const override;

    int parseBox(BitStream &bs, const char *type, uint32_t boxSize);

    ~TrackReferenceBox() override;
};


#endif //MP4DECODER_TRACKREFERENCEBOX_H
