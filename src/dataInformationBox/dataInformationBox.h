
#ifndef MP4DECODER_DATAINFORMATIONBOX_H
#define MP4DECODER_DATAINFORMATIONBOX_H

#include <vector>
#include "box.h"


class DataReferenceBox : public FullBox {
private:
    std::vector<Box> boxes;
    uint32_t entry_count;
public:
    DataReferenceBox(BitStream &bs, const char *boxType, uint32_t size);

    int parseBox(BitStream &bs, const char *boxType, uint32_t boxSize);
};

class DataEntryUrnBox : public FullBox {
private:
    char *name{nullptr};
    char *location{nullptr};
public:
    DataEntryUrnBox(BitStream &bs, const char *boxType, uint32_t size);

    ~DataEntryUrnBox() override;
};

/*数据引用对象包含一个数据引用表(通常为url)，它声明了在表示中使用的媒体数据的位置。
 * 样例描述中的数据引用索引将该表中的条目与赛道中的样例联系起来。
 * 一个音轨可以用这种方法在几个音源上分开。*/
class DataEntryUrlBox : public FullBox {
private:
    char *location;
public:
    DataEntryUrlBox(BitStream &bs, const char *boxType, uint32_t size);

    ~DataEntryUrlBox() override;
};


/*数据信息框包含声明媒体信息在音轨中的位置的对象。(dinf)*/
class DataInformationBox : public Box {
public:
    std::vector<Box> boxes;

    DataInformationBox(BitStream &bs, const char *boxType, uint32_t size);

    int parseBox(BitStream &bs, const char *boxType, uint32_t boxSize);
};

#endif //MP4DECODER_DATAINFORMATIONBOX_H
