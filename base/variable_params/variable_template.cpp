#include<iostream>
#include<string>
using namespace std;

template<typename ...Args>
using TFunc = int (*) (int i, Args...);

int test1(int i, int b, string c) {
	cout << "test1" << i << b << c.c_str() << endl;
	return 1;
}

int test2(int i, string b, string c) {
	cout << "test2" << i << b.c_str() << c.c_str() << endl;
	return 2;
}

int test3(int i, int c) {
	cout << "test3" << i << c << endl;
	return c;
}

template<typename ...Args>
void getHandle(TFunc<Args...> func, int i, Args... args) {
	(*func) (i, args...);
}

int main() {
	getHandle<int, string>(test1, 1, 2, "abc");
	getHandle<string, string>(test2, 2, "bbc", "bbb");
	getHandle<int>(test3, 3, 3);
	return 0;
}