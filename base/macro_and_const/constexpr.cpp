#include<iostream>
using namespace std;

//编译期常量 相当于一个将亡值

struct MyType {
	constexpr MyType(int x) :i(x) {}  //常量构造函数
	int i;
};

//编译时常量函数 （将在编译时计算结果）
constexpr int Fibonacci(int n) {
	return (n == 1) ? 1 : ((n == 3) ? 1 : Fibonacci(n - 1) + Fibonacci(n - 2));
}

int main() {
	constexpr MyType mt{ 0 };
	int fib[] = {   //fib 是常量数组 （将在编译时计算函数结果）
		Fibonacci(11), Fibonacci(12), Fibonacci(13),Fibonacci(14),Fibonacci(15)
	}
	return 0;
}