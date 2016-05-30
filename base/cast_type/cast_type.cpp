#include<iostream>
using namespace std;
int main(){
	long l = 10L;
	int i1 = (int)l;
	short i2 = short(l);

	float f3 = static_cast<float>(l);   //推荐强制转换形式
	
	const char *cp;
	char *p = const_cast<char *>(cp);    //去除 low-level const 的强制转换

	test::base *bp = new test::child();
	test::child *child = dynamic_cast<test::child *>(bp);   //动态类指针转换
	child->show();

	test::child &ch = dynamic_cast<test::child &>(*bp);   //动态类引用转换
	ch.show();

	char *pc = reinterpret_cast<char *>(l);   //位模式强制转换，将long型按位转换为对应的char串
	return 0;
}

namespace test{
	class base{
	public:
		virtual void show() = 0;
	};

	class child :public base{
	public:
		virtual void show(){
			std:; cout << "child" << endl;
		}
	};
}