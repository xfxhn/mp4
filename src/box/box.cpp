#include <cstring>
#include "box.h"
#include "bitStream.h"

Box::Box(BitStream &bs, const char *boxtype, uint32_t size, bool flag)
        : size(size), offset(8), containerBoxFlag(flag) {
    strcpy(type, boxtype);
    if (size == 1) {
        this->size = bs.readMultiBit(64);
        offset += 8;
    } else if (size == 0) {
        // box extends to end of file
    }
    if (strcmp(boxtype, "uuid") == 0) {
        //unsigned int(8)[16] usertype = extended_type;
        bs.getString(usertype, 16);
        offset += 16;
    }
}

std::vector<Box *> Box::getBoxes() const {
    return std::vector<Box *>();
}


/*Box::Box(const Box &a) : size(a.size), type(a.type) {

}*/

FullBox::FullBox(BitStream &bs, const char *boxtype, uint32_t size, bool flag)
        : Box(bs, boxtype, size, flag) {
    version = bs.readMultiBit(8);
    flags = bs.readMultiBit(24);
    offset += 4;
}

/*FullBox::~FullBox() {
    int aa = 1;
}*/

FullBox::FullBox(const FullBox &val) : Box(val) {
    version = val.version;
    flags = val.flags;
}
