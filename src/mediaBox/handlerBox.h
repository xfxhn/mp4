//
// Created by Administrator on 2022/4/28.
//

#ifndef MP4_HANDLERBOX_H
#define MP4_HANDLERBOX_H
#include "box.h"
/*声明当前track的类型，以及对应的处理器（handler）。*/
class HandlerBox : public FullBox {
public:
    /* ‘vide’    Video track
     * ‘soun’   Audio track
     * ‘hint’   Hint track
     * ‘meta’   Timed Metadata track
     * ‘auxv’   Auxiliary Video track
     * */
    char handler_type[5]{0};
    char *name;
public:
    HandlerBox(BitStream &bs, const char *boxType, uint32_t size);

    ~HandlerBox() override;
};
#endif //MP4_HANDLERBOX_H
