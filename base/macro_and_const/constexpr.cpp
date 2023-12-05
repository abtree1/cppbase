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

void check2(){
	// if constexpr 可以实现选择编译（相当于宏 #ifdef XXX）
	// 该例子只会编译 if（true）的部分
	if constexpr (sizeof(int) < sizeof(char)){
		cout << "sizeof(int) < sizeof(char)" << endl;
	}else{
		cout << "sizeof(int) >= sizeof(char)" << endl;
	}
}

// constinit 用于检测变量是否具有静态存储持续时间
constinit int x = 11;	//编译成功，全局变量具有静态存储持续时间
const char* f(){return "hello";}
constexpr const char* g(){return "cpp";}
int main() {
	constexpr MyType mt{ 0 };
	int fib[] = {   //fib 是常量数组 （将在编译时计算函数结果）
		Fibonacci(11), Fibonacci(12), Fibonacci(13),Fibonacci(14),Fibonacci(15)
	}

	constinit static int y = 42;	//编译成功，静态变量具有静态存储持续时间
	constinit int z = 7;		//编译失败，局部变量是动态分配的
	constinit const char* str1 = f();	//编译错误，f() 不是一个常量初始化函数
	constinit const char* str2 = g();	//编译成功
	return 0;
}