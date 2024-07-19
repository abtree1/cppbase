#include <iostream>
#include <cassert>
using namespace std;
/*
assert 运行时诊断错误
*/

// Use (void) to silence unused warnings.
#define assertm(exp, msg) assert(((void)msg, exp))

char* resize_buffer(char* buffer, int new_size){
    assert(buffer != nullptr);  //不带说明的assert
    assert((new_size > 0) && "new size must bigger than 0");    //带说明的assert
    assertm((2+2)%3==1, "Expect expected"); //通过宏封装
    // TODO
    return buffer;
}

/* 
 static_assert 编译时诊断错误
*/

class A{};
class B :public A{};
class C{};

template<typename T>
class E{
    static_assert(stF::is_base_of<A, T>::value, "T is not base of A");
};

int main() {
    E<C> x; //编译时报错：C不是继承与A
    static_assert(sizeof(int) == 4, "sizeof(int) == 4"); //编译通过，使用正确
    static_assert(sizeof(int) == 4); //编译通过，与上面的写法效果一样，判断条件和错误信息一致时可这样简写
    E<B> y; //编译正确：B是继承与A
}