#include <iostream>
#include <tuple>
#include <string>
using namespace std;

auto returnMultipleValues(){
    //多值返回是通过元祖实现的
    return make_tuple(11, 6);
}

struct BindTest{
    int a{1};
    string b {"Hello World"};
};

int main() {
    //结构化绑定可以自动解绑元祖
    auto [x, y] = returnMultipleValues();
    cout << x << " , " << y << endl;
    //结构化绑定还可以解码结构体
    BindTest bt;
    const auto [a, b] = bt; 
    cout << a << " , " << b.c_str() << endl;
    //结构化绑定数组
    int arr[3]{1,2,3};
    const auto [x1,x2,x3] = arr;
    cout << x1 << " , " << x2 << " , " << x3 << endl;
    return 0;
}