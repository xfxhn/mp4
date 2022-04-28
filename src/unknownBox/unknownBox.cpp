//
// Created by Administrator on 2022/4/28.
//

#include "unknownBox.h"
#include "bitStream.h"

UnknownBox::UnknownBox(BitStream &bs, const char *boxType, uint32_t size)
        : Box(bs, boxType, size) {
    uint32_t residueByte = size - offset;
    bs.readMultiBit(residueByte * 8);
}

