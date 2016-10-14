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

int main(){
	WSADATA	wsd; //加载winsock库，返回的库相关信息的结构
	//初始化套结字动态库
	int error = WSAStartup(MAKEWORD(2,2), &wsd); 
	if (error != 0) //MAKEWORD(WINSOCK次版本，WINSOCK主版本)
	{
		printf("WSAStartup failed!ErrorCode: %d \n", error);
		return -1;
	}

	/*
	*	参数：
	*	af：表示ip类型(IPv4:AF_INET)
	*	type:表示协议类型(TCP/IP:SOCK_STREAM, UDP/IP:SOCK_DGRAM)
	*	protocol:用于在给定地址族和套接字类型具有多重入口时，对具体的传送做限定
	*			(TCP:IPPROTO_TCP, UDP:IPPROTO_UDP)
	*/
	SOCKET sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(INVALID_SOCKET == sServer){
		puts("socket create failed!");
		WSACleanup();
		return -1;
	}
	//创建连接地址
	SOCKADDR_IN internetAddr;
	INT nPortId = 5150;
	internetAddr.sin_family = AF_INET;		//几乎固定值（表示ip协议类型）
	internetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//将port从主机存储顺序转换为网络存储顺序(htons)
	internetAddr.sin_port = htons(nPortId);
	/*
	*	参数:
	*	s:	绑定的SOCKET
	*	name:	这是一个地址缓冲区
	*	nameLen：地址缓冲区大小
	*/
	error = bind(sServer, (LPSOCKADDR)&internetAddr, sizeof(SOCKADDR_IN));
	if(SOCKET_ERROR == error){
		printf("socket bind failed! ErrorCode: %d", WSAGetLastError());
		closesocket(sServer);
		WSACleanup();
		return -1;
	}

	/*
	*	参数：
	*	s：	绑定的SOCKET
	*	backlog：允许同时请求的队列大小,超过的会直接返回失败,处理完成的请求会从队列移除，以便其它请求接入
	*/
	error = listen(sServer, 1);
	if(SOCKET_ERROR == error){
		printf("socket listen failed! ErrorCode: %d", WSAGetLastError());
		closesocket(sServer);
		WSACleanup();
		return -1;
	}

	SOCKADDR_IN addrClient;
	int addrClientLen = sizeof(SOCKADDR_IN);
	/*
	*	参数：
	*	s:监听的SOCKET
	*	addr：这是一个地址缓冲区，用于连接进来的SOCKET地址
	*	addrlen：地址缓冲区的大小
	*/
	SOCKET sClient = accept(sServer, (LPSOCKADDR)&addrClient, &addrClientLen);
	if(INVALID_SOCKET == sClient){
		printf("socket client accept failed! ErrorCode: %d", WSAGetLastError());
		closesocket(sServer);
		WSACleanup();
		return -1;
	}

	char buf[BUF_SIZE];
	/*
	*	参数：
	*	s: SOCKET
	*	buf: 接收缓冲
	*	len: 接收缓冲大小
	*	flags:(可按位或)
	*		0
	*		MSG_PEEK	接收采用复制形式，不从系统缓冲区删除原数据
	*		MSG_OOB		带外数据，即紧急数据
	*/
	error = recv(sClient, buf, BUF_SIZE, 0);
	puts(buf);

	closesocket(sClient);
	closesocket(sServer);

	error = WSACleanup(); //释放资源，对应 WSAStartup 函数
	if(error == SOCKET_ERROR){
		printf("WSACleanup Error! ErrorCode: %d \n", WSAGetLastError());
	}
	return 0;
}