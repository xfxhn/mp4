#include <cstring>
#include "sampleTableBox.h"
#include "bitStream.h"
#include "visualSampleEntry.h"
#include "audioSampleEntry.h"

SampleTableBox::SampleTableBox(BitStream &bs, const char *boxType, uint32_t size, const char *handler_type)
        : Box(bs, boxType, size), handler_type_(handler_type) {
    /*type 4 size 4*/
    while (offset < size) {
        uint32_t boxSize = bs.readMultiBit(32);
        offset += boxSize;
        char boxTypeName[5] = {0};
        bs.getString(boxTypeName, 4);
        parseBox(bs, boxTypeName, boxSize);
    }
}

int SampleTableBox::parseBox(BitStream &bs, const char *boxType, uint32_t boxSize) {

    if (strcmp(boxType, "stsd") == 0) {
        SampleDescriptionBox stsd(bs, "stsd", boxSize, handler_type_);
        boxes.push_back(stsd);
    } else if (strcmp(boxType, "stts") == 0) {
        TimeToSampleBox stts(bs, "stts", boxSize);
        boxes.push_back(stts);
    } else if (strcmp(boxType, "stsz") == 0) {
        SampleSizeBox stsz(bs, "stsz", boxSize);
        sample_count = stsz.sample_count;
        boxes.push_back(stsz);
    } else if (strcmp(boxType, "stz2") == 0) {
        CompactSampleSizeBox stz2(bs, "stz2", boxSize);
        boxes.push_back(stz2);
    } else if (strcmp(boxType, "stsc") == 0) {
        SampleToChunkBox stsc(bs, "stsc", boxSize);
        boxes.push_back(stsc);
    } else if (strcmp(boxType, "stco") == 0) {
        ChunkOffsetBox stco(bs, "stco", boxSize);
        boxes.push_back(stco);
    } else if (strcmp(boxType, "co64") == 0) {
        ChunkLargeOffsetBox co64(bs, "co64", boxSize);
        boxes.push_back(co64);
    } else if (strcmp(boxType, "stss") == 0) {
        SyncSampleBox stss(bs, "stss", boxSize);
        boxes.push_back(stss);
    } else if (strcmp(boxType, "ctts") == 0) {
        CompositionOffsetBox ctts(bs, "ctts", boxSize);
        boxes.push_back(ctts);
    } else if (strcmp(boxType, "sdtp") == 0) {
        SampleDependencyTypeBox sdtp(bs, "ctts", boxSize, sample_count);
        boxes.push_back(sdtp);
    }
    return 0;
}

/*stsd*/
SampleDescriptionBox::SampleDescriptionBox(BitStream &bs, const char *boxType, uint32_t size, const char *handler_type)
        : FullBox(bs, boxType, size) {


    int i;
    entry_count = bs.readMultiBit(32);
    offset += 4;
    /*type 4 size 4 version 1 flags 3 entry_count 4*/
    while (offset < size) {
        uint32_t boxSize = bs.readMultiBit(32);
        offset += boxSize;
        char boxTypeName[5] = {0};
        bs.getString(boxTypeName, 4);

        /*每组chunk里的sample对应的解码信息，
         * 比如说有两组sps和pps，这个chunk里的sample用第一个sps，pps，那个chunk里的sample用第二个sps，pps*/
        for (i = 1; i <= entry_count; ++i) {
            if (strcmp(handler_type, "soun") == 0) {// for audio tracks
                AudioSampleEntry soun(bs, boxTypeName, boxSize);
                boxes.push_back(soun);
            } else if (strcmp(handler_type, "vide") == 0) {// for video tracks
                VisualSampleEntry vide(bs, boxTypeName, boxSize);
                boxes.push_back(vide);
            } else if (strcmp(handler_type, "hint") == 0) {// Hint track

            } else if (strcmp(handler_type, "meta") == 0) {// Metadata track

            }
        }
        // parseBox(bs, boxTypeName, boxSize);
    }


}


TimeToSampleBox::TimeToSampleBox(BitStream &bs, const char *boxType, uint32_t size)
        : FullBox(bs, boxType, size) {
    /*表中条目的个数*/
    entry_count = bs.readMultiBit(32);
    sampleInfoList = new sampleInfo[entry_count];

    for (int i = 0; i < entry_count; ++i) {
        sampleInfoList[i].sample_count = bs.readMultiBit(32);
        sampleInfoList[i].sample_delta = bs.readMultiBit(32);
    }
}

TimeToSampleBox::~TimeToSampleBox() {
    if (sampleInfoList) {
        delete[] sampleInfoList;
        sampleInfoList = nullptr;
    }
}

SampleSizeBox::SampleSizeBox(BitStream &bs, const char *boxType, uint32_t size)
        : FullBox(bs, boxType, size) {

    /* 默认的sample大小（单位是byte），通常为0。
     * 如果sample_size不为0，那么，所有的sample都是同样的大小。
     * 如果sample_size为0，那么，sample的大小可能不一样 */
    sample_size = bs.readMultiBit(32);
    /*当前track里面的sample数目*/
    sample_count = bs.readMultiBit(32);
    if (sample_size == 0) {
        entry_size_list = new uint32_t[sample_count]();
        for (int i = 0; i < sample_count; ++i) {
            entry_size_list[i] = bs.readMultiBit(32);
        }
    }
}

SampleSizeBox::~SampleSizeBox() {
    if (entry_size_list) {
        delete[] entry_size_list;
        entry_size_list = nullptr;
    }
}

CompactSampleSizeBox::CompactSampleSizeBox(BitStream &bs, const char *boxType, uint32_t size)
        : FullBox(bs, boxType, size) {
    bs.readMultiBit(24);

    /*每个entry_size占据的位数（bit），可选的值为4、8、16*/
    field_size = bs.readMultiBit(8);
    sample_count = bs.readMultiBit(32);
    entry_size_list = new uint16_t[sample_count]();
    for (int i = 0; i < sample_count; ++i) {
        entry_size_list[i] = bs.readMultiBit(field_size);
    }
}

CompactSampleSizeBox::~CompactSampleSizeBox() {
    if (entry_size_list) {
        delete[] entry_size_list;
        entry_size_list = nullptr;
    }
}

SampleToChunkBox::SampleToChunkBox(BitStream &bs, const char *boxType, uint32_t size)
        : FullBox(bs, boxType, size) {
    entry_count = bs.readMultiBit(32);
    /*当前表项中，对应的第一个chunk的序号*/
    first_chunk = new uint32_t[entry_count];
    /*每个chunk包含的sample数*/
    samples_per_chunk = new uint32_t[entry_count];
    /*指向SampleDescriptionBox里的解码信息的index*/
    sample_description_index = new uint32_t[entry_count];
    for (int i = 0; i < entry_count; ++i) {
        first_chunk[i] = bs.readMultiBit(32);
        samples_per_chunk[i] = bs.readMultiBit(32);
        sample_description_index[i] = bs.readMultiBit(32);
    }
}

SampleToChunkBox::~SampleToChunkBox() {
    if (first_chunk) {
        delete[] first_chunk;
        first_chunk = nullptr;
    }
    if (samples_per_chunk) {
        delete[] samples_per_chunk;
        samples_per_chunk = nullptr;
    }
    if (sample_description_index) {
        delete[] sample_description_index;
        sample_description_index = nullptr;
    }
}

ChunkOffsetBox::ChunkOffsetBox(BitStream &bs, const char *boxType, uint32_t size)
        : FullBox(bs, boxType, size) {
    entry_count = bs.readMultiBit(32);
    /*chunk相对于文件的偏移量*/
    /*chunk_offset 指的是在文件本身中的 offset，而不是某个box内部的偏移。*/
    chunk_offsets = new uint32_t[entry_count]();
    for (uint32_t i = 0; i < entry_count; ++i) {
        chunk_offsets[i] = bs.readMultiBit(32);
    }
}

ChunkOffsetBox::~ChunkOffsetBox() {
    if (chunk_offsets) {
        delete[] chunk_offsets;
        chunk_offsets = nullptr;
    }
}

ChunkLargeOffsetBox::ChunkLargeOffsetBox(BitStream &bs, const char *boxType, uint32_t size)
        : FullBox(bs, boxType, size) {
    entry_count = bs.readMultiBit(32);
    chunk_offsets = new uint64_t[entry_count]();
    for (uint32_t i = 0; i < entry_count; ++i) {
        chunk_offsets[i] = bs.readMultiBit(64);
    }
}

ChunkLargeOffsetBox::~ChunkLargeOffsetBox() {
    if (chunk_offsets) {
        delete[] chunk_offsets;
        chunk_offsets = nullptr;
    }
}

SyncSampleBox::SyncSampleBox(BitStream &bs, const char *boxType, uint32_t size)
        : FullBox(bs, boxType, size) {
    /*entry_count：entry的条目数，可以认为是关键帧的数目；*/
    entry_count = bs.readMultiBit(32);
    /*sample_number：关键帧对应的sample的序号；（从1开始计算）*/
    sample_number = new uint32_t[entry_count]();
    for (uint32_t i = 0; i < entry_count; ++i) {
        sample_number[i] = bs.readMultiBit(32);
    }
}

SyncSampleBox::~SyncSampleBox() {
    if (sample_number) {
        delete[] sample_number;
        sample_number = nullptr;
    }
}

CompositionOffsetBox::CompositionOffsetBox(BitStream &bs, const char *boxType, uint32_t size)
        : FullBox(bs, boxType, size) {
    entry_count = bs.readMultiBit(32);
    /*连续相同 offset 的sample个数*/
    sample_count = new uint32_t[entry_count]();
    /*DTS和PTS之间的偏移量*/
    sample_offset = new uint32_t[entry_count]();
    for (uint32_t i = 0; i < entry_count; ++i) {
        sample_count[i] = bs.readMultiBit(32);
        sample_offset[i] = bs.readMultiBit(32);
    }
}

CompositionOffsetBox::~CompositionOffsetBox() {
    if (sample_count) {
        delete[] sample_count;
        sample_count = nullptr;
    }
    if (sample_offset) {
        delete[] sample_offset;
        sample_offset = nullptr;
    }
}

SampleDependencyTypeBox::SampleDependencyTypeBox(BitStream &bs, const char *boxType, uint32_t size,
                                                 uint32_t sample_count)
        : FullBox(bs, boxType, size) {
    /*
     *  is_leading=0 这个sample的重要性是未知的
     *  is_leading=1 这个sample是一个领先的示例，在引用的I-picture之前有一个依赖(因此是不可解码的);
     *  is_leading=2 这个sample不是领先的样品
     *  is_leading=3 这个sample是一个领先的示例，在引用的I-picture之前没有依赖关系(因此是可解码的);
     * */
    is_leading = new uint8_t[sample_count];

    /*
      0:  该样本的依赖性未知;
      1:  这个样本确实依赖于其他人(不是一个I帧);
      2:  这个样本不依赖于其他样本(I帧);
      3:  reserved
      */
    sample_depends_on = new uint8_t[sample_count];
    /*
     * 0:  其他样本对该样本的依赖性未知;
     * 1:  其他样品可能取决于这个(不是一次性的);
     * 2:  没有其他样品依赖于这个(一次性);
     * 3:  reserved*/
    sample_is_depended_on = new uint8_t[sample_count];
    /*
     * 0:  不知道该样本中是否存在冗余编码;
     * 1:  本sample中存在冗余编码;
     * 2:  在这个sample中没有冗余编码;
     * 3:  reserved */
    sample_has_redundancy = new uint8_t[sample_count];

    for (uint32_t i = 0; i < sample_count; ++i) {
        is_leading[i] = bs.readMultiBit(2);
        sample_depends_on[i] = bs.readMultiBit(2);
        sample_is_depended_on[i] = bs.readMultiBit(2);
        sample_has_redundancy[i] = bs.readMultiBit(2);
    }
}

SampleDependencyTypeBox::~SampleDependencyTypeBox() {
    if (is_leading) {
        delete[] is_leading;
        is_leading = nullptr;
    }
    if (sample_depends_on) {
        delete[] sample_depends_on;
        sample_depends_on = nullptr;
    }
    if (sample_is_depended_on) {
        delete[] sample_is_depended_on;
        sample_is_depended_on = nullptr;
    }
    if (sample_has_redundancy) {
        delete[] sample_has_redundancy;
        sample_has_redundancy = nullptr;
    }
}
