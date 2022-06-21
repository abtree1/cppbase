#include<iostream>
#include<string>

using namespace std;

int main() {
	const unsigned sz = 3;
	//初始化
	//不允许用一个数组直接拷贝初始化另一个数组
	int a1[sz] = { 0, 1, 2 };
	int a2[] = { 0, 1, 2 };
	int a3[5] = { 0, 1 };
	char a4[] = "iostream";

	int* ptrs[10];     //创建10个指针数组
	//int &refs[10];   //不允许创建引用数组
	int(*ptrss)[sz] = &a1;
	int(&refs)[sz] = a2;
	//遍历
	for (auto i : refs) {
		cout << i;
	}
	cout << endl;
	auto e = end(a1);
	for (auto p = a1; p != e; ++p) {
		cout << *p;
	}
	cout << endl;
	return 0;
}