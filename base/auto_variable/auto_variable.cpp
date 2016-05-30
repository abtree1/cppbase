#include<iostream>
using namespace std;

int main(){
	//auto 允许编译器自己判断变量的类型
	int i = 4;
	const int ci = i, &cr = ci;
	auto a = i;    //auto 推断 int
	auto v = 0;	   //auto 推断 int
	v = 2;
	auto *p = &i;  //auto 推断 int
	auto pp = &i;  //auto 推断 int *
	auto b = ci;  //auto 推断 int 
	auto c = cr;  //auto 推断 int
	auto d = &ci; //auto 推断 int *
	auto &g = ci; //auto 推断 const int
	//auto &h = 43; //非法
	const auto &j = 42;  //auto 推断 int

	//decltype() 获取变量或方法的类型
	decltype(ci) bb = 0;  //获取 bb 类型为 const int
	decltype(cr) cc = bb; //获取 cc 类型为 const int &
	decltype(f()) dd = 0; //获取 函数f() 返回值类型 dd 类型为 int
	decltype(ci + 1) ee = 0; //获取表达式返回值类型 ee 类型为 int
	decltype(*p) ff = i; //获取 ff 类型为 int &
	decltype((i)) gg = i; //获取 gg 类型为 int &
	return 0;
}

int f(){
	return 0;
}