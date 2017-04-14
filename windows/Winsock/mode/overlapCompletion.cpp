#include "stdafx.h"
SOCKET sNew;
char buff[BUFF_SIZE];
WSABUF dataBuff;

void CALLBACK WorkerRoutine(DWORD error, DWORD bytesTrans, LPWSAOVERLAPPED overlap, DWORD flags){
	DWORD sendBytes,recvBytes;
	if(error != 0 || bytesTrans == 0){
		//发生错误 关闭套接字
		closesocket(sNew);
		return;
	}
	//此时 一个重叠的wsarecv成功完成
	//现在可以接收数据
	memcpy(buff,buff + 1,bytesTrans - 1);  //收到的第一位为数据的编码标识 在此去除
	buff[bytesTrans - 1] = '\0';
	printf("recv data: %s \n", dataBuff.buf);
	//处理完成后 需要投递另外一个重叠的WSARecv 或 WSASend
	flags = 0;
	ZeroMemory(overlap,sizeof(WSAOVERLAPPED));
	dataBuff.len = BUFF_SIZE;
	dataBuff.buf = buff;
	if(WSARecv(sNew,&dataBuff,1,&recvBytes,&flags,overlap,WorkerRoutine) == SOCKET_ERROR){
		if(WSAGetLastError() != WSA_IO_PENDING){
			printf("WSARecv() failed with error %d \n", WSAGetLastError());
			return;
		}
	}
}

void overlapcompletion(){
	//启动一个winsock 建立监听套接字
	WSADATA	wsd;
	WSAEVENT eventArray[1];
	WSAOVERLAPPED acceptOverlapped;
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
	error = listen(sServer, 1);
	if(SOCKET_ERROR == error){
		printf("socket listen failed! ErrorCode: %d", WSAGetLastError());
		closesocket(sServer);
		WSACleanup();
		return;
	}
	//接受一个入站链接
	//sockaddr_in addrRemote;  
    //int nAddrLen = sizeof(addrRemote);  
	sNew = ::accept(sServer, NULL, NULL); //(SOCKADDR*)&addrRemote, &nAddrLen);  
	//已经有了一个接受套接字之后，开始使用带有完整历程的重叠i/o来处理i/o
	//为了启动重叠i/o处理 先提交一个重叠wsarecv
	DWORD recvBytes = 0,flags = 0;
	ZeroMemory(&acceptOverlapped, sizeof(WSAOVERLAPPED));
	dataBuff.len = BUFF_SIZE;
	dataBuff.buf = buff;

	//将wsaoverlapped结构指定为一个参数，在套接字上投递一个异步wsarecv请求并提供下面的
	//作为完成例程的workerroutine
	if(WSARecv(sNew,&dataBuff,1,&recvBytes,&flags,&acceptOverlapped,WorkerRoutine) == SOCKET_ERROR){
		if(WSAGetLastError() != WSA_IO_PENDING){
			printf("WSARecv() failed with error %d \n", WSAGetLastError());
			closesocket(sServer);
			WSACleanup();
			return;
		}
	}

	//因为WSAWaitForMultipleEvents() API 要求在一个或多个事件对象上等待
	//因此不得不创建一个伪事件，可以使用 SleepEx() api 代替
	eventArray[0] = WSACreateEvent();
	DWORD index = 0;
	while(true){
		index = WSAWaitForMultipleEvents(1,eventArray,FALSE,WSA_INFINITE,TRUE);
		if(index == WAIT_IO_COMPLETION){
			//一个重叠请求完成例程结束，继续为更多的完成例程服务
			continue;
		}else{
			//如果发生严重错误：停止处理
			//如果正在处理一个事件对象，那么这也就可能是事件数组的一个索引
			closesocket(sServer);
			WSACleanup();
			return;
		}
	}
	
	
	closesocket(sServer);
	error = WSACleanup(); //释放资源，对应 WSAStartup 函数
	if(error == SOCKET_ERROR){
		printf("WSACleanup Error! ErrorCode: %d \n", WSAGetLastError());
	}
}