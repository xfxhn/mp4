

#ifndef MP4DECODER_MOVIEBOX_H
#define MP4DECODER_MOVIEBOX_H

#include <vector>
#include "box.h"

/*mvhd针对整个影片，tkhd针对单个track，mdhd针对媒体，vmhd针对视频，smhd针对音频，可以认为是从 宽泛 > 具体，前者一般是从后者推导出来的。*/
class MovieHeaderBox : public FullBox {

private:
    uint64_t creation_time;
    uint64_t modification_time;
    /*文件媒体在1秒时间内的刻度值，可以理解为1秒长度的时间单元数*/
    uint32_t timescale;
    /*该track的时间长度，用duration和time scale值可以计算track时长，
     * 比如audio track的time scale = 8000, duration = 560128，时长为70.016，
     * video track的time scale = 600, duration = 42000，时长为70*/
    uint64_t duration;
    float rate;
    /*unsigned float rate1;*/
    float volume;
    uint32_t matrix[9]{};
    uint32_t pre_defined[6]{};
    uint32_t next_track_ID;
public:
    MovieHeaderBox(BitStream &bs, const char *boxtype, uint32_t size);

    MovieHeaderBox(const MovieHeaderBox &val);

    ~MovieHeaderBox() override = default;
};


class IODS : public FullBox {
private:

public:
    IODS(BitStream &bs, const char *boxtype, uint32_t size);
};

class MovieBox : public Box {
private:

    std::vector<Box> boxes;

public:
    MovieBox(BitStream &bs, const char *boxtype, uint32_t size);


    int parseBox(BitStream &bs, const char *type, uint32_t boxSize);
};


#endif //MP4DECODER_MOVIEBOX_H
