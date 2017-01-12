#include <iostream>
//winsock分两个主要版本
//每一版都有对应的dll文件

//第二版(大部分以WSA开头的函数为第二版函数)
#include<WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
//第一版
// #include<winsock.h>
// #pragma comment(lib, "wsock32.lib")
//特殊版
// #include<MSWSock.h>
// #pragma comment(lib, "mswsock.lib")

#define BUF_SIZE 64

/*********************************
	详细的的参数参考server.cpp
 ********************************/
int main(){
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData);

	SOCKET sendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	int port = 5051;
	SOCKADDR_IN recAddr;
	recAddr.sin_family = AF_INET;
	recAddr.sin_port = htons(port);
	recAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	char buf[BUF_SIZE];

	/*
	*	参数
	*	s：SOCKET
	*	buf：发送数据缓冲
	*	len：发送数据长度
	*	flags：0 MSG_OOB MSG_PEEK
	*	to：接收方的地址缓冲
	*	tolen：接收方地址缓存大小
	*/
	sendto(sendSocket, buf, BUF_SIZE, 0, (SOCKADDR *)&recAddr, sizeof(SOCKADDR_IN));

	closesocket(sendSocket);
	WSACleanup();
	return 0;
}