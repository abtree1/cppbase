#include<iostream>
using namespace std;

const int sz = 10;

//数组做参数或返回值情况

//最常用方式，占用内存也最少，但不直观，尤其是将数组备份到另一模块中时
void fun0(int *a){
	*(a + 6) = 9;
}

typedef int arrT[sz];
arrT *fun1(arrT *a){
	//操作
	(*a)[3] = 4;
	(*a)[1] *= 4;
	cout << (*a)[1] << endl;
	return a;
}

//type def的另一种方法，会多用空间 不推荐
int c[sz] = {};
decltype(c) *fun2(decltype(c) *a){
	//操作
	(*a)[4] = 5;
	(*a)[1] *= 5;
	cout << (*a)[1] << endl;
	return a;
}

int main(){
	int a[10] = { 1, 2, 3 };
	fun0(a);
	cout << a[6] << endl;
	arrT *b = fun1(&a);   //其实函数即实现了修改数组，又实现了拷贝数组
	cout << a[3] << " " << (*b)[3] << endl;
	decltype(c) *c = fun2(&a);
	cout << a[4] << " " << (*c)[4] << endl;
}