#include <cstring>
#include "box.h"
#include "bitStream.h"

Box::Box(BitStream &bs, const char *boxtype, uint32_t size)
        : type(boxtype), size(size) {

    if (size == 1) {
        this->size = bs.readMultiBit(64);
    } else if (size == 0) {
        // box extends to end of file
    }
    if (strcmp(boxtype, "uuid") == 0) {
        //unsigned int(8)[16] usertype = extended_type;
        this->type = "uuid";
    }
}

/*Box::Box(const Box &a) : size(a.size), type(a.type) {

}*/

FullBox::FullBox(BitStream &bs, const char *boxtype, uint32_t size)
        : Box(bs, boxtype, size) {
    version = bs.readMultiBit(8);
    flags = bs.readMultiBit(24);
}

/*FullBox::~FullBox() {
    int aa = 1;
}*/

FullBox::FullBox(const FullBox &val) : Box(val) {
    version = val.version;
    flags = val.flags;
}
