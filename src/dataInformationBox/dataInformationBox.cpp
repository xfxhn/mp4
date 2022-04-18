//
// Created by Administrator on 2022/4/18.
//

#include "dataInformationBox.h"

DataInformationBox::DataInformationBox(BitStream &bs, const char *boxType, uint32_t size)
        : Box(bs, boxType, size) {

}

int DataInformationBox::parseBox(BitStream &bs, const char *boxType, uint32_t boxSize) {
    return 0;
}

