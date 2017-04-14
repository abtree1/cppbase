#include "stdafx.h"

void overlapevent(){
	//启动一个winsock 建立监听套接字
	WSADATA	wsd;
	char buff[BUFF_SIZE];
	WSAEVENT eventArray[WSA_MAXIMUM_WAIT_EVENTS];
	DWORD total = 0;
	WSAOVERLAPPED acceptOverlapped;
	WSABUF dataBuff;
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
	SOCKET sNew = ::accept(sServer, NULL, NULL); //(SOCKADDR*)&addrRemote, &nAddrLen);  
	//建立一个重叠结构
	eventArray[total] = WSACreateEvent();
	ZeroMemory(&acceptOverlapped, sizeof(WSAOVERLAPPED));
	acceptOverlapped.hEvent = eventArray[total];
	dataBuff.len = BUFF_SIZE;
	dataBuff.buf = buff;
	++total;
	//投递一个wsarecv请求 以便开始在套接字上接收数据
	DWORD recvBytes = 0,flags = 0;  //flags 必须设置初始值0
	if(WSARecv(sNew,&dataBuff,1,&recvBytes,&flags,&acceptOverlapped, NULL) == SOCKET_ERROR){
		if(WSAGetLastError() != WSA_IO_PENDING){
			printf("error: %d \n", WSAGetLastError());
		}
	}

	//可将下面部分放在单独的线程中，让当前线程处理accept链接请求，从而扩展该机制

	//处理套接字上重叠消息
	while (true){
		DWORD index;
		//等候重叠i/o调用结束
		index = WSAWaitForMultipleEvents(total,eventArray,FALSE,WSA_INFINITE,FALSE);
		//索引为0 因为eventArray中只有一个事件
		//重置已传信事件
		WSAResetEvent(eventArray[index - WSA_WAIT_EVENT_0]);
		//确定重叠请求的状态
		DWORD bytesTrans;
		WSAGetOverlappedResult(sNew,&acceptOverlapped,&bytesTrans,FALSE,&flags);
		//先检查看通信对方是否已关闭链接，如果已关闭，则关闭套接字
		if(bytesTrans == 0){  //对方关闭连接时 bytesTrans 返回0
			printf("Closing socket %d \n", sNew);
			closesocket(sNew);
			WSACloseEvent(eventArray[index - WSA_WAIT_EVENT_0]);
			break;
		}
		//对接收到的数据处理
		memcpy(buff,buff + 1,bytesTrans - 1);  //收到的第一位为数据的编码标识 在此去除
		buff[bytesTrans - 1] = '\0';
		printf("recv data: %s \n", dataBuff.buf);
		//在套接字上投递另一个wsarecv请求
		flags = 0;
		ZeroMemory(&acceptOverlapped, sizeof(WSAOVERLAPPED));
		acceptOverlapped.hEvent = eventArray[index - WSA_WAIT_EVENT_0];
		dataBuff.len = BUFF_SIZE;
		dataBuff.buf = buff;

		if(WSARecv(sNew, &dataBuff,1,&recvBytes,&flags,&acceptOverlapped,NULL) == SOCKET_ERROR){
			if(WSAGetLastError() != WSA_IO_PENDING){
				printf("error: %d \n", WSAGetLastError());
			}
		}
	}
	closesocket(sServer);
	error = WSACleanup(); //释放资源，对应 WSAStartup 函数
	if(error == SOCKET_ERROR){
		printf("WSACleanup Error! ErrorCode: %d \n", WSAGetLastError());
	}
}