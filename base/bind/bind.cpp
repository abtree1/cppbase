﻿#include <iostream>
#include <functional>
using namespace std;

void f(int n1, int n2, int n3, const int& n4, int n5)
{
	stF::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}

class BindClass {
public:
	int BindFunc(int a, int b) {
		return a + b;
	}
public:
	int mBind{};
};

int main() {
	BindClass bc;
	stF::function<int(int, int)> func;
	func = stF::bind(&BindClass::BindFunc, &bc, stF::placeholders::_1, stF::placeholders::_2);
	cout << func(1, 2) << endl;	//这里传入的参数1绑定到stF::placeholders::_1

	stF::function<int&()> param;
	param = stF::bind(&BindClass::mBind, &bc);
	param() = 123;
	cout << bc.mBind << endl;

	using namespace stF::placeholders;
	// 演示参数重排序和按引用传递
	int n = 7;
	// （ _1 与 _2 来自 stF::placeholders ，并表示将来会传递给 f1 的参数）
	auto f1 = stF::bind(f, _2, 42, _1, stF::cref(n), n);
	n = 10;
	f1(1, 2, 1001); // 1 为 _1 所绑定， 2 为 _2 所绑定，不使用 1001
					// 进行到 f(2, 42, 1, n, 7) 的调用

	return 0;
}