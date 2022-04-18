
#ifndef MP4DECODER_MEDIAINFORMATIONBOX_H
#define MP4DECODER_MEDIAINFORMATIONBOX_H

#include <vector>
#include "box.h"

/*视频流和音频流(例如，定时元数据流)可以使用一个空的媒体头框，如这里定义的。*/
class NullMediaHeaderBox : public FullBox {
public:
    NullMediaHeaderBox(BitStream &bs, const char *boxType, uint32_t size);
};


/*提示媒体报头包含与协议无关的一般信息，用于提示跟踪。 (PDU是协议数据单元。) (hmhd) */
class HintMediaHeaderBox : public FullBox {
private:
    uint16_t maxPDUsize;
    uint16_t avgPDUsize;
    uint32_t maxbitrate;
    uint32_t avgbitrate;
public:
    HintMediaHeaderBox(BitStream &bs, const char *boxType, uint32_t size);
};


/*声音媒体标头包含独立于编码的音频媒体的一般表示信息。 此标题用于包含音频的所有音轨。  */
class SoundMediaHeaderBox : public FullBox {
private:
    /*音频的均衡是用来控制计算机的两个扬声器的声音混合效果，一般值是0。*/
    uint16_t balance;
public:
    SoundMediaHeaderBox(BitStream &bs, const char *boxType, uint32_t size);
};



/*vmhd*/
/*视频媒体头包含独立于编码的用于视频媒体的一般表示信息。 注意，flags字段的值为1。*/
class VideoMediaHeaderBox : public FullBox {
private:
    uint16_t graphicsmode;
    uint16_t opcolor[3]{0};
public:
    VideoMediaHeaderBox(BitStream &bs, const char *boxType, uint32_t size);
};

/*此框包含所有声明轨道中介质特征信息的对象。(mdia)*/
class MediaInformationBox : public Box {
public:
    std::vector<Box> boxes;

    MediaInformationBox(BitStream &bs, const char *boxType, uint32_t size);

    int parseBox(BitStream &bs, const char *boxType, uint32_t boxSize);
};

#endif //MP4DECODER_MEDIAINFORMATIONBOX_H
