#include<iostream>
using namespace std;

/*
 * bool        布尔类型(true,false)
 * char		   字符(根据平台不同，可能解析为有符号和无符号)
 * signed char    为了解决跨平台问题，可以将char显示声明为signed或unsigned
 * unsigned char 
 * wchar_t     宽字符
 * char16_t    Unicode字符
 * char32_t    Unicode字符
 * short       短int
 * unsigned short
 * int         整形
 * unsigned int 
 * long        长int,现在long型常常与int型相同，因此，如果表示大整形，建议使用long long型
 * unsigned long
 * long long   长int
 * unsigned long long
 * float       单精度浮点型
 * double      双精度浮点型
 * long double 扩张精度浮点型
 */
int main(){
	bool b = true;
	char c = 'a';
	signed char _sc = 97;
	unsigned char _uc = 97;
	wchar_t wc = L'a';
	char16_t c16 = 'a';
	char32_t c32 = 'a';
	short si = 1;
	unsigned short _usi = 1;
	int i = 1;
	unsigned int _ui = 1;
	long l = 1;
	unsigned long _ul = 1;
	long long ll = 1;
	unsigned long long _ull = 1;
	float f = 0.23F;
	double d = 0.45;
	long double ld = 1.32;

	//四种变量初始化的方法 目前似乎还不完全支持
	/*int a = 0;
	int b = { 0 };
	int c{ 0 };
	int d(0);*/

	cout << "bool: " << b << endl			// 1
		<< "char: " << c << endl			// a
		<< "wchar_t: " << wc << endl		// 97
		<< "char16_t: " << c16 << endl		// 97
		<< "char32_t: " << c32 << endl		// 97
		<< "short: " << si << endl			// 1
		<< "int: " << i << endl				// 1
		<< "long: " << l << endl			// 1
		<< "long long: " << ll << endl		// 1
		<< "float: " << f << endl			// 0.23
		<< "double: " << d << endl			// 0.45
		<< "long double: " << ld << endl;   // 1.32
	//<< "a,b,c,d" << a << b << c << d << endl;

	return 0;
}