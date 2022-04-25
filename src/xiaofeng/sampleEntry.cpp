
#include <cstdio>
#include "sampleEntry.h"
#include "bitStream.h"

SampleEntry::SampleEntry(BitStream &bs, const char *format, uint32_t size)
        : Box(bs, format, size) {
    bs.readMultiBit(48);
    offset += 6;
    /*当MP4文件的数据部分，可以被分割成多个片段，每一段对应一个索引，并分别通过URL地址来获取，
    此时，data_reference_index 指向对应的片段（比较少用到）；*/
    data_reference_index = bs.readMultiBit(16);
    offset += 2;
}



