

#ifndef MP4DECODER_FILETYPEBOX_H
#define MP4DECODER_FILETYPEBOX_H

#include "box.h"

class FileTypeBox : public Box {
private:
    char major_brand[5]{0};
    uint32_t minor_version;
    const char **compatible_brands;
    uint32_t residualByte;
public:
    FileTypeBox(BitStream &bs, const char *boxtype, uint32_t size);

    ~FileTypeBox() override;
};

#endif //MP4DECODER_FILETYPEBOX_H
