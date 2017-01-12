/***
兼容IPv6的新写法
***/
#include <iostream>

#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#define BUF_SIZE 64

int main(){
	WSADATA	wsd;
	int rc = WSAStartup(MAKEWORD(2, 2), &wsd);
    if (rc != 0) {
        printf("WSAStartup failed: %d\n", rc);
        return 1;
    }
	
	addrinfo hints, *result;
	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_NUMERICHOST;	//不同的地址用不同的解析标记,另外标记可以为空(此时任意地址类型都可以)
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	int rc = getaddrinfo("127.0.0.1", "8081", &hints, &result);
	if(rc != 0){
		printf("getaddrinfo failed: %d\n", rc);
        return 1;
	}

	SOCKET s = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if(s  == INVALID_SOCKET){
		printf("create socket failed: %d\n", rc);
        return 1;
	}

	rc = connect(s, result->ai_addr, result->ai_addrlen);
	if(rc == SOCKET_ERROR){
		printf("connect failed: %d\n", rc);
        return 1;
	}

	/**
	此处省略代码 参考
		client.cpp
	**/

	freeaddrinfo(result);
    WSACleanup();
}