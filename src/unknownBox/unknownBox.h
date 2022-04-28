
#ifndef MP4_UNKNOWNBOX_H
#define MP4_UNKNOWNBOX_H

/*定义那些暂时没解析的，或者未知的，自定义的box*/
#include "box.h"

class UnknownBox : public Box {
public:
    UnknownBox(BitStream &bs, const char *boxType, uint32_t size);
};

#endif //MP4_UNKNOWNBOX_H
