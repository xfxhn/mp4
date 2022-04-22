#include <cstring>
#include "box.h"
#include "bitStream.h"

Box::Box(BitStream &bs, const char *boxtype, uint32_t size)
        : type(boxtype), size(size), offset(8) {

    if (size == 1) {
        this->size = bs.readMultiBit(64);
        offset += 8;
    } else if (size == 0) {
        // box extends to end of file
    }
    if (strcmp(boxtype, "uuid") == 0) {
        //unsigned int(8)[16] usertype = extended_type;

        char *extended_type = new char[16 + 1]();
        bs.getString(extended_type, 16);
        this->type = "uuid";
        offset += 16;
    }
}

/*Box::Box(const Box &a) : size(a.size), type(a.type) {

}*/

FullBox::FullBox(BitStream &bs, const char *boxtype, uint32_t size)
        : Box(bs, boxtype, size) {
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
