#include "audioSampleEntry.h"
#include "bitStream.h"


AudioSampleEntry::AudioSampleEntry(BitStream &bs, const char *codingname, uint32_t size)
        : SampleEntry(bs, codingname, size) {
    bs.readMultiBit(32);
    bs.readMultiBit(32);
    channelcount = bs.readMultiBit(16);
    samplesize = bs.readMultiBit(16);
    pre_defined = bs.readMultiBit(16);
    bs.readMultiBit(16);
    samplerate = bs.readMultiBit(32) >> 16u;
    int a = 1;
}
