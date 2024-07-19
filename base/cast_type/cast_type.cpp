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
	int addr_l = reinterpret_cast<int>(&l);	//取出l的地址 并保存为int
	/* link_l的地址与l一样，因此link_l == l
	   修改link_l也会修改l
	   这一步的操作就等于 long* link_l = &l;
	*/
	long* link_l = reinterpret_cast<long*>(addr_l);	//
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
			stF:; cout << "child" << endl;
		}
	};
}