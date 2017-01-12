#define _UNICODE
#define UNICODE

#include <iostream>
#include <string>
#include <tchar.h>
#include <Windows.h>

using namespace std;

int main(){
	char source[256] = "这是测试用例!";
	int souLen = MultiByteToWideChar(CP_ACP, 0, source, -1, NULL, 0);  //获取长度
	//TCHAR* target = new TCHAR[souLen + 1];
	//wmemset(target,0,souLen + 1);
	//memset(target, 0, souLen*2 + 2);
	TCHAR* target = (TCHAR *)HeapAlloc(GetProcessHeap(), 0, souLen*sizeof(TCHAR));
	if(target == NULL){
		GetLastError();
		return 0;
	}
	MultiByteToWideChar(CP_ACP,0,source,-1,target,souLen);  //执行转换操作

	souLen = WideCharToMultiByte(CP_UTF8, 0, target, -1, NULL, 0, NULL, NULL);  //换一种编码格式转换回来（ANSI -> UTF8）
	//char* utf8Tar = new char[souLen + 1];
	//memset(utf8Tar,0, souLen + 1);
	char* utf8Tar = (char*)HeapAlloc(GetProcessHeap(), 0, souLen);
	if(utf8Tar == NULL){
		GetLastError();
		return 0;
	}
	WideCharToMultiByte(CP_UTF8,0,target,-1,utf8Tar,souLen,NULL,NULL);  //将宽字符串转换为等价的多字节字符串
	string str(utf8Tar);
	HeapFree(GetProcessHeap(),0, target);
	HeapFree(GetProcessHeap(),0,utf8Tar);
	//delete [] target;
	//delete [] utf8Tar;

	return 0;
}