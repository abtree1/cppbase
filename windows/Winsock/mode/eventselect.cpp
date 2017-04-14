#include "stdafx.h"

SOCKET gSocketArray[WSA_MAXIMUM_WAIT_EVENTS];
WSAEVENT gEventArray[WSA_MAXIMUM_WAIT_EVENTS];
DWORD gTotal = 0; 

void compressArrays(DWORD index){
	//未实现功能
}

void eventselect(){
	WSADATA	wsd; 
	int error = WSAStartup(MAKEWORD(2,2), &wsd); 
	if (error != 0)
	{
		printf("WSAStartup failed!ErrorCode: %d \n", error);
		return;
	}
	SOCKET sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(INVALID_SOCKET == sServer){
		puts("socket create failed!");
		WSACleanup();
		return;
	}
	SOCKADDR_IN internetAddr;
	INT nPortId = 5150;
	internetAddr.sin_family = AF_INET;		
	internetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	internetAddr.sin_port = htons(nPortId);
	error = bind(sServer, (LPSOCKADDR)&internetAddr, sizeof(SOCKADDR_IN));
	if(SOCKET_ERROR == error){
		printf("socket bind failed! ErrorCode: %d", WSAGetLastError());
		closesocket(sServer);
		WSACleanup();
		return;
	}
	WSAEVENT newEvent =  WSACreateEvent();
	WSAEventSelect(sServer, newEvent, FD_ACCEPT|FD_CLOSE);
	error = listen(sServer, 1);
	if(SOCKET_ERROR == error){
		printf("socket listen failed! ErrorCode: %d", WSAGetLastError());
		closesocket(sServer);
		WSACleanup();
		return;
	}

	gSocketArray[gTotal] = sServer;
	gEventArray[gTotal] = newEvent;
	++gTotal;

	DWORD index;
	WSANETWORKEVENTS networkEvents;
	while (true){
		//这里会阻塞等待 一次最多等待64个socket
		index = WSAWaitForMultipleEvents(gTotal,gEventArray,FALSE,WSA_INFINITE,FALSE);
		index = index - WSA_WAIT_EVENT_0;
		//遍历所有事件 查看被传信的事件是否多于1个
		for(DWORD i = index;i<gTotal; ++i){
			index = WSAWaitForMultipleEvents(1,&gEventArray[i],TRUE,1000,FALSE);
			if((index == WSA_WAIT_FAILED) || (index == WSA_WAIT_TIMEOUT))
				continue;
			index = i;
			WSAEnumNetworkEvents(gSocketArray[index],gEventArray[index],&networkEvents);
			if(networkEvents.lNetworkEvents & FD_ACCEPT){
				if(networkEvents.iErrorCode[FD_ACCEPT_BIT] != 0){
					printf("FD_ACCEPT failed with  error %d \n", networkEvents.iErrorCode[FD_ACCEPT_BIT]);
					break;
				}
				SOCKADDR_IN addrClient;
				int len = sizeof(SOCKADDR);
				gSocketArray[gTotal] = ::accept(gSocketArray[index], (SOCKADDR*)&addrClient, &len);
				//无法处理多余WSA_MAXIMUM_WAIT_EVENTS数量的套接字，故关闭接收套接字
				if(gTotal > WSA_MAXIMUM_WAIT_EVENTS){
					printf("Too many connection. \n");
					closesocket(gSocketArray[gTotal]);
					break;
				}

				gEventArray[gTotal] = WSACreateEvent();
				WSAEventSelect(gSocketArray[gTotal],gEventArray[gTotal],FD_READ|FD_WRITE|FD_CLOSE);
				printf("Socket %d connected \n", gSocketArray[gTotal]);
				++gTotal;
			}
			//处理读入
			if(networkEvents.lNetworkEvents & FD_READ){
				if(networkEvents.iErrorCode[FD_READ_BIT] != 0){
					printf("FD_READ failed with error %d \n", networkEvents.iErrorCode[FD_READ_BIT]);
					break;
				}
				//从套接字读入数据
				char buff[BUFF_SIZE];
				::recv(gSocketArray[index-WSA_WAIT_EVENT_0],buff, sizeof(buff),0);
				printf("recv data : %s \n", buff);
			}
			//处理FD_WRITE
			if(networkEvents.lNetworkEvents & FD_WRITE){
				if(networkEvents.iErrorCode[FD_WRITE_BIT] != 0){
					printf("FD_WRITE failed with error %d \n", networkEvents.iErrorCode[FD_WRITE_BIT]);
					break;
				}
				char buff[BUFF_SIZE] = "This is a Test!";
				::send(gSocketArray[index - WSA_WAIT_EVENT_0], buff, sizeof(buff), 0);
			}
			//关闭
			if(networkEvents.lNetworkEvents & FD_CLOSE){
				if(networkEvents.iErrorCode[FD_CLOSE_BIT] != 0){
					printf("FD_CLOSE failed with error %d \n", networkEvents.iErrorCode[FD_CLOSE_BIT]);
					break;
				}
				closesocket(gSocketArray[index]);
				//移除事件和socket 并减小total计数
				compressArrays(index);
			}
		}
	}	

	closesocket(sServer);
	error = WSACleanup();  //释放资源，对应 WSAStartup 函数
	if(error == SOCKET_ERROR){
		printf("WSACleanup Error! ErrorCode: %d \n", WSAGetLastError());
	}
}