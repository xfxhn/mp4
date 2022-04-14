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


int main() {
    /*B test1(5, 6);
    B test2(test1);
    B test3(move(B(1, 2)));*/
    Decoder decode;
    decode.init("resouce/movie.mp4");
    return 0;
}