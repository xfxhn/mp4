#include "decoder.h"

/*#include <iostream>

using namespace std;

class A {
public:
    int aa{0};
    int *bb{nullptr};

    A(int aa, int bb) : aa(aa), bb(new int(bb)) {
        cout << "执行了A的构造函数" << endl;
    }

    A(const A &val) {
        aa = val.aa;
        bb = new int(*val.bb);
        cout << "执行了A的拷贝构造函数" << endl;
    }

    A(A &&val) noexcept {
        cout << "执行A的移动构造" << endl;
        bb = val.bb;
        val.bb = nullptr;
    }

    ~A() {
        if (bb) {
            delete bb;
            bb = nullptr;
        }
    }
};

class B : public A {
public:
    int *b{nullptr};

    B(int aa, int bb) : A(aa, bb) {
        b = new int(213);
    }

    B(const B &val) : A(val) {
        b = new int(*val.b);
    }

    B(B &&val) noexcept: A(move(val)) {
        b = val.b;
        val.b = nullptr;
    }

    ~B() {
        if (b) {
            delete b;
            b = nullptr;
        }
    }
};*/

#define BigLittleSwap32(A)  ((((uint32)(A) & 0xff000000) >> 24) |   \
                            (((uint32)(A) & 0x00ff0000) >> 8)   |   \
                            (((uint32)(A) & 0x0000ff00) << 8)   |   \
                            (((uint32)(A) & 0x000000ff) << 24))





// 模拟htonl函数，本机字节序转网络字节序

/*unsigned long int t_htonl(unsigned long int h) {

    // 若本机为大端，与网络字节序同，直接返回

    // 若本机为小端，转换成大端再返回

    return checkCPUendian() ? h : BigLittleSwap32(h);

}*/


#include <vector>
#include <iostream>

using namespace std;

uint64_t test1(uint64_t val) {
    char *a = (char *) &val;
    uint64_t ret = 0;
    for (int i = 0; i < 8; ++i) {
        uint8_t b = *(a + i);
        ret = b | (ret << ((unsigned) 8));
    }
    return ret;
}

class A {
public:
    int a = 12;

    A() {

    }

    /*A(const A &a) {
        cout << "111" << endl;
    }

    A(A &&a) {
        cout << "aaaaaaaaaa" << endl;
    }*/

    virtual ~A() = default;
};

class B : public A {
public:
    B() {

    }

    /*B(const B &b) {
        cout << "bbbb" << endl;
    }

    B(B &&b) {
        cout << "aaaaaaaaaaaaaa" << endl;
    }*/

    int b = 24;
};


int main() {
    uint8_t startCode[5] = {0, 0, 0, 1, 254};
    std::ofstream fout;
    fout.open("output/aaa.h264", std::ios::binary | std::ios::out | std::ios::trunc);
    if (fout.is_open()) {
        fout.write(reinterpret_cast<const char *>(startCode), 5);
    }
    fout.close();
    Decoder decode;
    decode.init("resouce/movie.mp4");
    return 0;
}