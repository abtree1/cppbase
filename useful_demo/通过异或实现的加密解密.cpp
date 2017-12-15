#include <iostream>
#include <string>

using namespace std;

/*
通过异或加密解密
其原理是一个字符（z）与另一个字符(&)异或
&^z -> / (加密)
在将
&^/ -> z (解密)
*/
int main(){
	string source = "this is a test!";
	char key = '&';
	string target ="";
	for(char &ch : source){
		target += key^ch;
	}
	cout << "encode: " << target.c_str() << endl;
	string decode = "";
	for(char &ch : target){
		decode += key^ch;
	}
	cout << "decode: " << decode.c_str() << endl;
	return 0;
}