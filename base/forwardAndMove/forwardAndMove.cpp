#include <iostream>
using namespace std;

template<typename T>
using Func = void (T::*)(int);

//这是一个实现完美转发的例子 实现了参数校验
template<typename T, typename U>
void TPerfectForward(T &&t, U* a, Func<U> pFunc) {
	cout << t << "\t forwarded..." << endl;
	(a->*pFunc)(std::forward<T>(t));
};

class A {
public:
	A() 
		:m(0)
		,md(new double){
	}
	A(A& a)							//拷贝构造函数
		:m(a.m)
		,md(new double(*a.md)){
	}
	A(A &&a)						//移动构造函数
		:m(move(a.m))    //move 返回左值的右值
		,md(a.md){
		a.md = nullptr;			//此处必须把指针设置为空指针 不然会被析构掉
	}
	~A() {					//显示定义了析构函数后 拷贝和移动构造函数默认不生成
		delete md;
	}
public:
	void setA(int a) { 
		m = a; 
	}
	int getA() { return m; }
private:
	int m = 0;
	double *md;
};

int main() {
	A a;
	TPerfectForward<int, A>(10, &a, &A::setA);
	A b(move(a));
	cout << "a value" << a.getA() << "b value: " << b.getA() << endl;
	a.setA(20);
	cout << "a value" << a.getA() << "b value: " << b.getA() << endl;
	return 0;
}