#include "stdafx.h"

void select(){
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
	error = listen(sServer, 1);
	if(SOCKET_ERROR == error){
		printf("socket listen failed! ErrorCode: %d", WSAGetLastError());
		closesocket(sServer);
		WSACleanup();
		return;
	}

	//select begin..................................................................
	// FD_ZERO（*set） 将set初始化为空集合，集合在使用前都要清空
	// FD_CLR (s, *set) 从set中删除s 
	// FD_ISSET（s, *set） 是否是set成员(TRUE-FALSE)
	// FD_SET(s,*set) s加入set
	fd_set fdSocket;
    FD_ZERO(&fdSocket);  
    FD_SET(sServer, &fdSocket); 

	while(fdSocket.fd_count>0)
	{
		fd_set fdRead = fdSocket;  
		//param
		// nfds  无用（berkeley 保留部分）
		// readfds  可读取或监听fds
		// writefds  可写入（发送）fds
		// exceptfds  其它fds
		// timeout   超时
        int nRet = ::select(0, &fdRead, NULL, NULL, NULL);  
        if(nRet > 0)  
        {  
            for(int i=0; i<(int)fdSocket.fd_count; ++i)  
            {  
                if(FD_ISSET(fdSocket.fd_array[i], &fdRead))  //select 会删除没有状态的s  这里做检查
                {  
                    if(fdSocket.fd_array[i] == sServer)    
                    {  
                        if(fdSocket.fd_count < FD_SETSIZE)  //FD_SETSIZE 为select最大允许的连接数
                        {  
                            sockaddr_in addrRemote;  
                            int nAddrLen = sizeof(addrRemote);  
                            SOCKET sNew = ::accept(sServer, (SOCKADDR*)&addrRemote, &nAddrLen);  
							if(sNew  == INVALID_SOCKET)//error
							{
								FD_CLR(sServer, &fdSocket);
							}
							else{
								FD_SET(sNew, &fdSocket);  
								printf("A new connect success(%s) \n", ::inet_ntoa(addrRemote.sin_addr));  
							}
                        }  
                        else  
                        {  
                            printf(" Too much connections! \n");  
                            continue;  
                        }  
                    }  
                    else  
                    {  
                        char szText[BUFF_SIZE];  
                        int nRecv = ::recv(fdSocket.fd_array[i], szText, sizeof(szText) - 1, 0);
						szText[nRecv] = '\0'; 
                        if(nRecv > 0)                        
                        {
							int sendCount,currentPosition=0;
							while( nRecv>0 && (sendCount=send(fdSocket.fd_array[i] ,szText+currentPosition,nRecv,0))!=SOCKET_ERROR)
							{
								nRecv-=sendCount;
								currentPosition+=sendCount;
							}
							if(sendCount==SOCKET_ERROR){
								printf("sen error %s \n", szText);  
								::closesocket(fdSocket.fd_array[i]);  
								FD_CLR(fdSocket.fd_array[i], &fdSocket);
							}								;
                        }  
                        else
                        {
							printf("close a client\n"); 
                            ::closesocket(fdSocket.fd_array[i]);  
                            FD_CLR(fdSocket.fd_array[i], &fdSocket);  
                        }  
                    }  
                }  
            }  
        }  
        else  
        {  
            printf(" Failed select() \n");  
            break;  
        }  
	}

	closesocket(sServer);

	error = WSACleanup(); //释放资源，对应 WSAStartup 函数
	if(error == SOCKET_ERROR){
		printf("WSACleanup Error! ErrorCode: %d \n", WSAGetLastError());
	}
}

