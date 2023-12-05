#include <iostream>
using namespace std;

/* 命名空间可以保证命名的隔离性
    inline 关键字可以将命名空间中的命名导出到父命名空间中
    他的使用场景为：
    假如某个库升级了库函数，但为了兼容老的用户需求
    新用户可以使用
        A::foo()
    默认使用新的foo函数的实现
    而想使用老的foo函数的实现的用户可以显示使用
        A::B::foo()
    使用特定的foo()函数的实现，以保证兼容性
*/
namespace A {
    namespace B{
        void foo(){
            cout << "foo version B" << endl;
        }
    }
    inline namespace C{
        void foo(){
            cout << "foo version C current def" << endl;
        }
    }
}

/**命名空间的简写形式***********************/
namespace A{
    namespace B{
        namespace C{
            void foo(){
                cout << "foo version B" << endl;
            }
        }
    }
}
namespace A{
    inline namespace B{
        namespace C{
            void foo(){
                cout << "foo version B" << endl;
            }
        }
    }
}
/**简写为**********************************/
namespace A::B::C{
    void foo(){
        cout << "foo version B" << endl;
    }
}
namespace A::inline B::C{
    void foo(){
        cout << "foo version B" << endl;
    }
}
/******************************************/

int main() {
    return 0;
}