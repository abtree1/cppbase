#include <iostream>
using namespace std;

/* 字节对齐对功能实现往往没有任何影响
   但是对程序执行效率，有较大的影响
*/

//不使用字节对齐
struct X {
    char a1;
    int a2;
    double a3;
};

//所有成员都是16字节对齐
struct X1 {
    alignas(16) char a1;
    alignas(double) int a2;
    double a3;
};

//所有成员都是16字节对齐
struct alignas(16) X2 {
    char a1;
    int a2;
    double a3;
};

//所有成员都是16字节对齐
struct alignas(16) X3 {
    alignas(8) char a1; //不生效
    alignas(double) int a2;
    double a3;
};

// alignas(4) < 成员字节对齐长度，无效
// 成员以各自的字节对齐长度对齐
struct alignas(4) X4 {
    alignas(8) char a1;
    alignas(double) int a2;
    double a3;
};

int main() {
    //获取int的字节对齐长度
    auto x1 = alignof(int);
    //获取函数指针的字节对齐长度
    auto x2 = alignof(void(*)());
    cout << x1 << " , " << x2 << endl;
    return 0;
}