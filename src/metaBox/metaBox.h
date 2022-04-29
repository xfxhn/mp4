
#ifndef MP4_METABOX_H
#define MP4_METABOX_H

#include <vector>
#include "box.h"

class MetaBox : public FullBox {
private:
    std::vector<Box *> boxes;
public:
    MetaBox(BitStream &bs, const char *boxType, uint32_t size);

    std::vector<Box *> getBoxes() const override;

    int parseBox(BitStream &bs, const char *boxType, uint32_t boxSize);

    ~MetaBox() override;
};

#endif //MP4_METABOX_H
