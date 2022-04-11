
#include "FileTypeBox.h"
#include "bitStream.h"

FileTypeBox::FileTypeBox(BitStream &bs, const char *boxtype, uint32_t size)
        : Box(bs, boxtype, size) {

    bs.getString(major_brand, 4);
    minor_version = bs.readMultiBit(32);

    residualByte = size - bs.position;
    compatible_brands = new const char *[residualByte / 4];
    for (int i = 0; i < residualByte / 4; i++) {
        char *str = new char[5]();
        bs.getString(str, 4);
        compatible_brands[i] = str;
    }
}

FileTypeBox::~FileTypeBox() {
    if (compatible_brands) {
        for (int i = 0; i < residualByte / 4; ++i) {
            delete[] compatible_brands[i];
            compatible_brands[i] = nullptr;
        }
        delete[] compatible_brands;
        compatible_brands = nullptr;
    }
}
