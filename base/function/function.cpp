#include<iostream>
#include<functional>
using namespace std;

//使用追踪返回类型推导
template<typename T, typename U>
auto sum(T a, U b) -> decltype(a + b){
	return a + b;
}

int add(int a, int b){
	return a + b;
}

int main(){
	function<int(int, int)> f1 = add;  //作为函数指针
	decltype(&add) f3 = &add;  //和上面相同
	function<int(int, int)> f2 = [](int a, int b){ return a - b; }; //保存lambda表达式
	cout << f1(2, 3) << endl;
	cout << f2(3, 2) << endl;
	result_of<decltype(&add)(int,int)>::type h = (*f3)(4,5);  //通过result_of 获取返回类型
	cout << h << endl;
	auto g = sum(123 + 34.6d);  //g is double
	cout << g << endl;  
	return 0;
}