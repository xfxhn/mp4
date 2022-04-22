#ifndef MP4DECODER_SAMPLETABLEBOX_H
#define MP4DECODER_SAMPLETABLEBOX_H

#include <vector>
#include "box.h"


/*这个可选table回答了关于sample 依赖的3个问题*/
/*这个可选的表回答了关于示例依赖关系的三个问题:
  1)这个样本是否依赖于其他人(例如，它是一个I-picture)?
  2)没有其他的样品依赖于这个吗?
  3)此示例是否包含此时间-瞬间(可能具有不同的依赖关系)的数据的多个(冗余)编码?
 */
/*在没有这个表的情况下:
  1)同步样本表(部分)回答了第一个问题; 在大多数视频编解码器中，i -picture也是同步点，
  2)其他样本对该样本的依赖性未知。
  3)冗余编码的存在未知。
  */
class SampleDependencyTypeBox : public FullBox {
private:
    uint8_t *is_leading{nullptr};
    uint8_t *sample_depends_on{nullptr};
    uint8_t *sample_is_depended_on{nullptr};
    uint8_t *sample_has_redundancy{nullptr};
public:
    SampleDependencyTypeBox(BitStream &bs, const char *boxType, uint32_t size, uint32_t sample_count);

    ~SampleDependencyTypeBox() override;
};


class CompositionOffsetBox : public FullBox {
private:
    uint32_t entry_count;
    uint32_t *sample_count;
    uint32_t *sample_offset;
public:
    CompositionOffsetBox(BitStream &bs, const char *boxType, uint32_t size);

    ~CompositionOffsetBox() override;
};

/*mp4文件中，关键帧所在的sample序号。如果没有stss的话，所有的sample中都是关键帧*/
class SyncSampleBox : public FullBox {
private:
    uint32_t entry_count;
    uint32_t *sample_number{nullptr};
public:
    SyncSampleBox(BitStream &bs, const char *boxType, uint32_t size);

    ~SyncSampleBox() override;
};


/*两种不同的box类型(stco、co64) 32位或64位偏移量。后者在管理非常大的演示文稿时非常有用。在样本表的任何单个实例中，最多只会出现其中一个变体。*/
class ChunkOffsetBox : public FullBox {
private:
    uint32_t entry_count;
    uint32_t *chunk_offsets{nullptr};
public:
    ChunkOffsetBox(BitStream &bs, const char *boxType, uint32_t size);

    ~ChunkOffsetBox() override;
};

class ChunkLargeOffsetBox : public FullBox {
private:
    uint32_t entry_count;
    uint64_t *chunk_offsets{nullptr};
public:
    ChunkLargeOffsetBox(BitStream &bs, const char *boxType, uint32_t size);

    ~ChunkLargeOffsetBox() override;
};


/*stsc*/
/*sample 以 chunk 为单位分成多个组。chunk的size可以是不同的，chunk里面的sample的size也可以是不同的。*/
class SampleToChunkBox : public FullBox {
private:
    uint32_t entry_count;
    uint32_t *first_chunk;
    uint32_t *samples_per_chunk;
    uint32_t *sample_description_index;
public:
    SampleToChunkBox(BitStream &bs, const char *boxType, uint32_t size);

    ~SampleToChunkBox() override;
};



/*stsz*/
/*每个sample的大小（字节），根据 sample_size 字段，可以知道当前track包含了多少个sample（或帧）*/
class SampleSizeBox : public FullBox {
public:
    uint32_t sample_size;
    uint32_t sample_count;
    uint32_t *entry_size_list{nullptr};
public:
    SampleSizeBox(BitStream &bs, const char *boxType, uint32_t size);

    ~SampleSizeBox() override;
};

/*stz2*/
class CompactSampleSizeBox : public FullBox {
private:
    uint8_t field_size;
    uint32_t sample_count;
    uint16_t *entry_size_list{nullptr};
public:
    CompactSampleSizeBox(BitStream &bs, const char *boxType, uint32_t size);

    ~CompactSampleSizeBox() override;
};

/*stts*/
class TimeToSampleBox : public FullBox {
private:
    struct sampleInfo {
        uint32_t sample_count{0};
        uint32_t sample_delta{0};
    };
    uint32_t entry_count;
    sampleInfo *sampleInfoList{nullptr};
public:
    TimeToSampleBox(BitStream &bs, const char *boxType, uint32_t size);

    ~TimeToSampleBox() override;
};

class SampleDescriptionBox : public FullBox {
private:
    std::vector<Box> boxes;
    uint32_t entry_count;
public:
    SampleDescriptionBox(BitStream &bs, const char *boxType, uint32_t size, const char *handler_type);
};

class SampleTableBox : public Box {
private:
    uint32_t sample_count{0};
    std::vector<Box> boxes;

    const char *handler_type_;
public:
    SampleTableBox(BitStream &bs, const char *boxType, uint32_t size, const char *handler_type);

    int parseBox(BitStream &bs, const char *boxType, uint32_t boxSize);
};

#endif //MP4DECODER_SAMPLETABLEBOX_H
