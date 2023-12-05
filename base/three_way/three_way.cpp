#include <iostream>
#include <vector>
using namespace std;

//定义了 <=> 就相当于同时定义了 >, >=, <, <=, 只需再定义一个==运算符，就定义了所有关系运算符
// template<typename T>
// std::strong_ordering operator<=>(const std::vector<T>& lhs,const std::vector<T>& rhs){
//     size_t min_size = min(lhs.size(), rhs.size());
//     for(size_t i = 0; i< min_size;++i){
//         if (auto const cmp = std::compare_three_way(lhs[i], rhs[i]); cmp != 0){
//             return cmp;
//         }
//     }
//     return lhs.size() <=> rhs.size();
// }

// 只需要重载 <=> 和 == 就实现了 >, >=, <, <= , == , != 六个操作符重载
struct Legacy{
    int n{};
    bool operator==(const Legacy& rhs) const{
        return n == rhs.n;
    }
    std::strong_ordering operator<=>(const Legacy& rhs) const{
        return n <=> rhs.n;
    }
};

struct ThreeWay{
    Legacy m{};
    std::strong_ordering operator<=>(const ThreeWay &rhs) const{
        return m <=> rhs.m;
    }
    bool operator==(const ThreeWay &rhs) const{
        return m == rhs.m;
    }
};

int main() {
    bool b = (7 <=> 11) < 0;
    cout << boolalpha << b << endl;

    ThreeWay t1, t2;
    t1.m.n = 1;
    t2.m.n = 2;
    // b = t1 < t2;
    cout << boolalpha << (t1 > t2) << endl;
    cout << boolalpha << (t1 != t2) << endl;
    return 0;
}