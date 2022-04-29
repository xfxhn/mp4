
#ifndef MP4DECODER_MEDIABOX_H
#define MP4DECODER_MEDIABOX_H

#include <vector>
#include "box.h"

/*媒体标头声明了与媒体无关的总体信息，并且与轨道中媒体的特征相关。*/
class MediaHeaderBox : public FullBox {
private:
    uint64_t creation_time;
    uint64_t modification_time;
    uint32_t timescale;
    uint64_t duration;
    uint8_t pad;
    /*语种名称代码 ISO 639-2标准*/
    char language[4]{0};
    uint16_t pre_defined;
public:
    MediaHeaderBox(BitStream &bs, const char *boxType, uint32_t size);
};


/*mdia 媒体声明容器包含在一个音轨内声明有关媒体数据信息的所有对象。  */
class MediaBox : public Box {
private:
    std::vector<Box *> boxes;
    char handler_type[5]{0};
public:
    MediaBox(BitStream &bs, const char *boxType, uint32_t size);

    std::vector<Box *> getBoxes() const override;

    int parseBox(BitStream &bs, const char *boxType, uint32_t boxSize);

    ~MediaBox() override;
};

#endif //MP4DECODER_MEDIABOX_H
