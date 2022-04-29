

#ifndef MP4_USERDATABOX_H
#define MP4_USERDATABOX_H

#include <vector>
#include "box.h"

class NameBox : public Box {
public:
    NameBox(BitStream &bs, const char *boxType, uint32_t size);

};


/*此box包含一些对象，这些对象声明关于包含box及其数据(表示或跟踪)的用户信息。*/
/*用户数据box是用于提供信息的用户数据的容器。这个用户数据被格式化为一组具有更特定框类型的框，这些框更精确地声明了它们的内容。*/
class UserDataBox : public Box {
private:
    std::vector<Box *> boxes;
public:
    UserDataBox(BitStream &bs, const char *boxType, uint32_t size);

    std::vector<Box *> getBoxes() const override;

    int parseBox(BitStream &bs, const char *boxType, uint32_t boxSize);

    ~UserDataBox() override;
};

#endif //MP4_USERDATABOX_H
