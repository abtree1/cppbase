#include<iostream>
#include<cstring>   //c 语言的string
#include<string>    //c++ 的string
using namespace std;
int main(){
	const char *str1 = "hello ";
	string str2 = "world!";
	cout << "str1 length: " << strlen(str1) << endl;  //计算长度
	if (strcmp(str1, str2.c_str()) > 0){
		cout << "str1 bigger" << endl;
	}else{
		cout << "str2 bigger" << endl;
	}
	cout << "str2 + str1: " << strcat((char *)str2.c_str(), str1) << endl;
	cout << "str2 >> str1: " << strcpy((char *)str2.c_str(), str1) << endl;
	return 0;
}