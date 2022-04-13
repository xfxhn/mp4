

#ifndef MP4DECODER_MOVIEBOX_H
#define MP4DECODER_MOVIEBOX_H

#include <vector>
#include "box.h"

class MovieHeaderBox : public FullBox {
public:
    MovieHeaderBox(BitStream &bs, const char *boxtype, uint32_t size);
};

class MovieBox {
private:
    const char *boxtype;
    uint32_t size;

    std::vector<Box> boxes;

public:
    MovieBox(BitStream &bs, const char *boxtype, uint32_t size);


    int parseBox(BitStream &bs,const char *type, uint32_t boxSize);
};


#endif //MP4DECODER_MOVIEBOX_H
