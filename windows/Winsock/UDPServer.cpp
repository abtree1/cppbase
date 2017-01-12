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

	SOCKET recvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	int port = 5050;
	SOCKADDR_IN receiverAddr;
	receiverAddr.sin_family = AF_INET;
	receiverAddr.sin_port = htons(port);
	receiverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	SOCKADDR_IN sendAddr;
	bind(recvSocket, (SOCKADDR*)&sendAddr, sizeof(SOCKADDR_IN));

	char recvBuf[BUF_SIZE];
	int len = sizeof(SOCKADDR_IN);
	/*
	*	参数：
	*	s：SOCKET
	*	buf：接收数据的buf
	*	len：buf的size
	*	flags：0 MSG_OOB MSG_PEEK
	*	from：发送方addr缓存池
	*	fromlen：发送缓存地址大小
	*/
	recvfrom(recvSocket, recvBuf, BUF_SIZE, 0, (SOCKADDR*)&sendAddr, &len);

	closesocket(recvSocket);
	WSACleanup();

	return 0;
}