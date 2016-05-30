#include<iostream>
#include<functional>
using namespace std;

int add(int a, int b){
	return a + b;
}

int main(){
	function<int(int, int)> f1 = add;  //作为函数指针
	function<int(int, int)> f2 = [](int a, int b){ return a - b; }; //保存lambda表达式
	cout << f1(2, 3) << endl;
	cout << f2(3, 2) << endl;
	return 0;
}