#include "stdafx.h"
SYSTEM_INFO systemInfo;
typedef enum{
	RECV_POSTED,
	SEND_POSTED
}OPERATION_TYPE;
typedef struct _PER_HANDLE_DATA{
	SOCKET socket;
	SOCKADDR_STORAGE clientAddr;
}PER_HANDLE_DATA;
typedef struct{
	OVERLAPPED overlapped;
	char buffer[BUFF_SIZE];
	int buffLen;
	OPERATION_TYPE operationType;
}PER_IO_DATA;

DWORD WINAPI serverWorkerThread(LPVOID lpParam){
	//工作器处理
	HANDLE compPort = (HANDLE)lpParam;
	DWORD bytesTransfor;
	LPOVERLAPPED overlapped;
	PER_HANDLE_DATA *perHandleData;
	PER_IO_DATA *perIoData;
	DWORD sendBytes = 0,recvBytes = 0, flags = 0;
	while(true){
		//等待和完成端口关联的任意套接字i/o完成(这里可能是无序的)
		BOOL ret = GetQueuedCompletionStatus(compPort,&bytesTransfor,(LPDWORD)&perHandleData,(LPOVERLAPPED*)&perIoData,INFINITE);
		//先检查一下，看看是否在套接字上已有错误发生
		//如果发生了 关闭套接字 并清除和这个套接字关联的单句柄数据和单i/o操作数据
		if(bytesTransfor == 0 && (perIoData->operationType == RECV_POSTED || perIoData->operationType == SEND_POSTED)){
			//bytesTransfor == 0 时表示套接字已被通信对方关闭 因此我们也要关闭套接字
			//注意：单句柄数据用来引用和i/o关联的套接字
			closesocket(perHandleData->socket);
			GlobalFree(perHandleData);
			GlobalFree(perIoData);
			continue;
		}

		//为完成的i/o请求服务，可以通过查看单i/o操作数据中包含的operationType 字段
		//来确定刚完成的是哪个i/o请求
		if(perIoData->operationType == RECV_POSTED){
			//处理收到的数据
			char *buff = new char[bytesTransfor + 1];
			memcpy(buff, perIoData->buffer + 1, bytesTransfor);
			buff[bytesTransfor] = '\0';
			std::cout << buff << std::endl;
			delete [] buff;
		}

		//投递另一个wsasend或wsarecv
		flags = 0;
		ZeroMemory(&(perIoData->overlapped), sizeof(OVERLAPPED));
		WSABUF wbuf;
		wbuf.buf = perIoData->buffer;
		wbuf.len = BUFF_SIZE;
		perIoData->operationType = RECV_POSTED;
		WSARecv(perHandleData->socket,&wbuf,1,&recvBytes,&flags,&(perIoData->overlapped), NULL);
	}
	return 0;
}

void completionport(){
	WSADATA wsd;
	int error = WSAStartup(MAKEWORD(2,2), &wsd); 
	if (error != 0)
	{
		printf("WSAStartup failed!ErrorCode: %d \n", error);
		return;
	}
	//创建一个i/o完成端口
	HANDLE compPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,0);
	//获取系统相关信息
	GetSystemInfo(&systemInfo);
	//基于系统中可用的处理器数量创建工作器线程
	//我们每个处理器创建一个线程
	for(int i =0; i < systemInfo.dwNumberOfProcessors; ++i){
		HANDLE threadHandle;
		//创建一个服务器的工作器线程，并将完成端口传递到该线程
		threadHandle = CreateThread(NULL,0,serverWorkerThread,compPort,0,NULL);
		if(threadHandle == NULL){
			printf("Create Thread Failed! \n");
		}
		//关闭线程句柄
		CloseHandle(threadHandle);
	}
	//创建一个监听套接字
	SOCKET listen = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	SOCKADDR_IN internetAddr;
	INT nPortId = 5150;
	internetAddr.sin_family = AF_INET;		
	internetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	internetAddr.sin_port = htons(nPortId);
	error = bind(listen, (LPSOCKADDR)&internetAddr, sizeof(SOCKADDR_IN));
	if(SOCKET_ERROR == error){
		printf("socket bind failed! ErrorCode: %d", WSAGetLastError());
		closesocket(listen);
		WSACleanup();
		return;
	}

	//让套接字为监听做好准备
	error = ::listen(listen, 1);
	if(SOCKET_ERROR == error){
		printf("socket listen failed! ErrorCode: %d", WSAGetLastError());
		closesocket(listen);
		WSACleanup();
		return;
	}

	while(true){
		PER_HANDLE_DATA* perHandleData = NULL;
		SOCKADDR_IN saRemote;
		int remoteLen = sizeof(saRemote);
		SOCKET accept = ::accept(listen,(SOCKADDR*)&saRemote,&remoteLen);
		//创建用来和套接字关联的单句柄数据信息结构
		perHandleData = (PER_HANDLE_DATA*)GlobalAlloc(GPTR, sizeof(PER_HANDLE_DATA));
		printf("Socket number %d connected \n", accept);
		perHandleData->socket = accept;
		memcpy(&perHandleData->clientAddr, &saRemote,remoteLen);
		//将接受套接字和完成端口关联起来
		CreateIoCompletionPort((HANDLE)accept,compPort,(DWORD)perHandleData,0);
		//开始在接受套接字上处理i/o
		//使用重叠i/o，在套接字上投递一个或多个WSASend() 或 WSARecv()调用
		PER_IO_DATA perIOData;
		WSABUF wbuf;
		DWORD bytes,flags = 0;
		ZeroMemory(&(perIOData.overlapped), sizeof(WSAOVERLAPPED));
		wbuf.buf = perIOData.buffer;
		wbuf.len = sizeof(perIOData.buffer);
		perIOData.operationType = RECV_POSTED;
		if(WSARecv(accept,&wbuf,1,&bytes,&flags,&(perIOData.overlapped),NULL) == SOCKET_ERROR){
			if(WSAGetLastError() != WSA_IO_PENDING){
				printf("WSARecv() failed with error %d \n", WSAGetLastError());
				return;
			}
		}

	}
	PostQueuedCompletionStatus(compPort, 0xFFFFFFFF, 0, NULL);
	CloseHandle(compPort);
	closesocket(listen);
	WSACleanup();
}