#include<iostream>
#include<string>
using namespace std;

void prints1(initializer_list<string> il){
	cout << "size: " << il.size() << endl;
	for (auto s = il.begin() ; s != il.end(); ++s){
		cout << *s << endl;
	}
	for (auto s : il){
		cout << s << endl;
	}
}

void prints2(int count, ...){
	cout << count << endl;
	va_list params = NULL;
	_crt_va_start(params, count);
	for (int i = 0; i < count; ++i){
		string s = _crt_va_arg(params, string);
		cout << s << endl;
	}
	_crt_va_end(params);
}

void prints3(char c,...){  //最后一个参数是char c
	va_list params = 0;
	_crt_va_start(params, c);  //使指针知道最后一个参数是什么
	string s = _crt_va_arg(params, string);
	int i = _crt_va_arg(params, int);
	float f = _crt_va_arg(params, double);  //此处不能使用float
	_crt_va_end(params);
	cout << "string: " << s << endl;
	cout << "int: " << i << endl;
	cout << "float: " << f << endl;
}

int main(){
	string s1 = "aaaaa";
	string s2 = "bbbbb";
	string s3 = "ccccc";
	initializer_list<string> il = { s1, s2, s3 };
	prints1(il);
	
	
	prints2(3, s1, s2, s3);
	prints3('e', s1, 2, 3.1f);
	return 0;
}