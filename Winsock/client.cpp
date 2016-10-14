#include <iostream>
//winsock分两个主要版本
//每一版都有对应的dll文件

//第二版
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
		return 1;
	}

	//创建套接字
	SOCKET sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	
	if(INVALID_SOCKET == sClient)
	{
		printf("socket create failed! ErrorCode:%d \n", WSAGetLastError());
		WSACleanup();//释放套接字资源
		return  -1;
	}

	//创建连接地址
	SOCKADDR_IN internetAddr;
	INT nPortId = 5151;
	internetAddr.sin_family = AF_INET;		//几乎固定值（表示ip协议类型）
	//将点分地址转换为4字节整数，分配给sin_addr
	internetAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//将port从主机存储顺序转换为网络存储顺序(htons)
	internetAddr.sin_port = htons(nPortId);

	/*
	*	参数：
	*	s:监听的SOCKET
	*	addr：这是一个地址缓冲区，用于连接进来的SOCKET地址
	*	addrlen：地址缓冲区的大小
	*/
	error = connect(sClient, (LPSOCKADDR)&internetAddr, sizeof(SOCKADDR_IN));
	if(SOCKET_ERROR == error){
		printf("connect failed! ErrorCode:%d \n", WSAGetLastError());	
		closesocket(sClient);
		WSACleanup();
		return -1;
	}

	char buf[BUF_SIZE] = "hello, world!";

	/*
	*	参数：
	*	s: SOCKET
	*	buf: 发送的字节缓冲区指针
	*	len: 发送的字节长度
	*	flags:	(可按位或)
	*		0				
	*		MSG_DONTROUTE
	*		MSG_OOB(带外数据，即紧急数据)
	*
	*	返回发送成功的数据
	*/
	size_t len = strlen(buf);
	size_t pos = 0;
	while(len > 0){
		error = send(sClient, &buf[pos], len, 0);
		len -= error;
		pos += error;
	}

	/*
	*	完成断连前的清理操作，保证所有数据收发完成
	*	参数：
	*	how: 
	*		SD_SEND		停止发送
	*		SD_RECEIVE	停止接收
	*		SD_BOTH		两者都停止
	*/
	shutdown(sClient,SD_BOTH);
	
	closesocket(sClient);

	error = WSACleanup(); //释放资源，对应 WSAStartup 函数
	if(error == SOCKET_ERROR){
		printf("WSACleanup Error! ErrorCode: %d \n", WSAGetLastError());
	}
	return 0;
}