/**
IPv4和IPv6采用双堆栈机制,IPv4一个堆栈，IPv6 一个堆栈
**/

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <vector>

int main(){
	WSADATA	wsd; //加载winsock库，返回的库相关信息的结构
	//初始化套结字动态库
	int error = WSAStartup(MAKEWORD(2,2), &wsd); 
	if (error != 0) //MAKEWORD(WINSOCK次版本，WINSOCK主版本)
	{
		printf("WSAStartup failed!ErrorCode: %d \n", error);
		return -1;
	}

	addrinfo hints, *res = NULL, *ptr = NULL;
	char szPort[] =  "5150";
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	int rc = getaddrinfo(NULL, szPort, &hints, &res);
	if(rc != 0){
		//错误处理
	}

	ptr = res;
	std::vector<SOCKET> sockets;
	SOCKET sock;
	while (ptr){
		sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if(sock == INVALID_SOCKET){
			//错误处理
		}

		rc = bind(sock, ptr->ai_addr, ptr->ai_addrlen);
		if(rc != 0){
			//错误处理
		}

		rc = listen(sock, 7);
		if(rc == SOCKET_ERROR){
			//错误处理
		}
		sockets.push_back(sock);
		ptr = ptr->ai_next;
	}

	return 0;
}