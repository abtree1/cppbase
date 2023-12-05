#include <iostream>
#include <vector>
using namespace std;

int main() {
    //带初始化的for
    vector<int> vec{1,2,3,4,5};
    cout << "[";
    for(bool b = true; auto i : vec){
        if (b) {
            b = false;
        }else{
            cout << ", ";
        }
        cout << i;
    }
    cout << "]" << endl;

    //带初始化的if
    if(bool b1 = [](){return true;}; b1){
        //初始化可以调用函数
        //可以访问b1
    }else if(bool b2 = false; b2){
        //可以访问b1和b2
    }else{
        //可以访问b1和b2
    }
    
    //带初始化的switch
    int typ = 1;
    switch (bool b = true; typ)
    {
    case 1:
        cout << boolalpha << b << " " << typ << endl;
        break;
    default:
        break;
    }
    return 0;
}