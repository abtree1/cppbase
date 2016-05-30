#include<iostream>
#include<vector>
using namespace std;

/*
* lambda 结构 => auto f = [函数对象参数](操作符重载函数参数)mutable或exception声明->返回值类型{函数体}
* 函数对象参数：
*	空			不传对象参数
*	=			以值传递传入对象参数（包括this指针）
*	&			以引用方式传入对象参数（包括this指针）
*	this		传入对象的this指针
*	a			传入对象中变量a（值传递）
*	&a			传入对象中变量a（引用传递）
*	a,&b		a值传递，b引用传递
*	=,a,&b		值传入所有对象参数，且a值传递，b引用传递
*	&,a,&b		引用传入所有对象参数，且a值传递，b引用传递
*操作符重载函数参数
*	调用lambda时传入的参数
*mutable或exception声明
*	可省略
*返回值类型
*	标识返回值类型
*函数体
*/
class Test{
public:
	Test() :m_data(10){}
	~Test(){}

	void test_lambda(){
		vector<int> vec{ 1, 2, 3, 4, 5 };

		auto f = [](int v){cout << v << endl; };
		for (auto a : vec){
			f(a);
		}

		int x = 10;
		auto f1 = [=](int v){cout << v + x << endl; };
		for (auto b:vec){
			f1(b);
		}

		auto f2 = [this, &x](int v){ 
			cout << x << " " << this->m_data << " " << v << endl;
			return x + v*this->m_data; };
		for (auto b : vec){
			x = f2(b);
		}
		cout << x << endl;

		auto f3 = [this, &x](int v)->int{ return x + v*this->m_data; };
		for (auto b : vec){
			x = f3(b);
		}
		cout << x << endl;
	}
private:
	int m_data;
};

int main(){
	Test t;
	t.test_lambda();
	return 0;
}