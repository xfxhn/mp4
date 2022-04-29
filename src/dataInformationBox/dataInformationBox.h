
#ifndef MP4DECODER_DATAINFORMATIONBOX_H
#define MP4DECODER_DATAINFORMATIONBOX_H

#include <vector>
#include "box.h"

/*当一个文件的数据条目设置了标志，表明媒体数据在同一个文件中，当该文件被分割为多个段进行传输时，
 * 该标志的值不会改变，因为该文件在传输操作后(逻辑上)被重新组装(dref)*/
class DataReferenceBox : public FullBox {
private:
    std::vector<Box *> boxes;
    uint32_t entry_count;
public:
    DataReferenceBox(BitStream &bs, const char *boxType, uint32_t size);

    std::vector<Box *> getBoxes() const override;

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
    std::vector<Box *> boxes;

    DataInformationBox(BitStream &bs, const char *boxType, uint32_t size);

    std::vector<Box *> getBoxes() const override;

    int parseBox(BitStream &bs, const char *boxType, uint32_t boxSize);

    ~DataInformationBox() override;
};

#endif //MP4DECODER_DATAINFORMATIONBOX_H
