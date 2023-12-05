#include <iostream>
#include <vector>
#include <string>
using namespace std;
//与struct结合可以将多个值压缩为一个值
union Key{
    struct{
        unsigned int first : 16;
        unsigned int second : 16;
    } A;
    unsigned int B{};
};

unsigned int GetKey(unsigned short p1,unsigned short p2){
    Key key;
    key.A.first = p1;
    key.A.second = p2;
    return key.B;
}

//c++ 20 联合类型支持高级成员，但需要手动添加构造和析构函数
union U{
    U():x3(){
    }
    ~U(){
        x3.~basic_string();
    }
    int x1;
    double x2;
    string x3;
    vector<int> x4;
};

int main() {
    cout << GetKey(1,1) << endl;
    U u;
    //此时x3已经有了构造和析构函数，所以可以直接使用
    u.x3 = "hello world";
    cout << u.x3.c_str() << endl;
    //x4还没有构造与析构所以不能直接使用，但可以通过下面的方式使用
    new(&u.x4) std::vector<int>;    //手动构造
    u.x4.push_back(1);
    cout << u.x4[0] << endl;
    u.x4.~vector(); //手动析构(这里似乎有些问题)
    return 0;
}