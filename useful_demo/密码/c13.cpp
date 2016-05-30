#include"c11.h"
#include<iostream>
#include<string>
using namespace std;

ft f;

//简单的将字母向后移4位，现在有别的解决方案
int main()
{
	f.in();
	f.out();

	//新的方法
	string str;
	cout << "input a string" << endl;
	cin >> str;
	for (auto &c : str){
		if (isalpha(c)){
			c += 4;
			if (c > 'z'){
				c -= 'z';
			}
		}else{
			c = '*';
		}
	}
	cout << str << endl;
	return 0;
}

