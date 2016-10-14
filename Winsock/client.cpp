#include <iostream>
//winsock��������Ҫ�汾
//ÿһ�涼�ж�Ӧ��dll�ļ�

//�ڶ���
#include<WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
//��һ��
// #include<winsock.h>
// #pragma comment(lib, "wsock32.lib")
//�����
// #include<MSWSock.h>
// #pragma comment(lib, "mswsock.lib")

#define BUF_SIZE 64

int main(){
	WSADATA	wsd; //����winsock�⣬���صĿ������Ϣ�Ľṹ
	//��ʼ���׽��ֶ�̬��
	int error = WSAStartup(MAKEWORD(2,2), &wsd); 
	if (error != 0) //MAKEWORD(WINSOCK�ΰ汾��WINSOCK���汾)
	{
		printf("WSAStartup failed!ErrorCode: %d \n", error);
		return 1;
	}

	//�����׽���
	SOCKET sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	
	if(INVALID_SOCKET == sClient)
	{
		printf("socket create failed! ErrorCode:%d \n", WSAGetLastError());
		WSACleanup();//�ͷ��׽�����Դ
		return  -1;
	}

	//�������ӵ�ַ
	SOCKADDR_IN internetAddr;
	INT nPortId = 5151;
	internetAddr.sin_family = AF_INET;		//�����̶�ֵ����ʾipЭ�����ͣ�
	//����ֵ�ַת��Ϊ4�ֽ������������sin_addr
	internetAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//��port�������洢˳��ת��Ϊ����洢˳��(htons)
	internetAddr.sin_port = htons(nPortId);

	/*
	*	������
	*	s:������SOCKET
	*	addr������һ����ַ���������������ӽ�����SOCKET��ַ
	*	addrlen����ַ�������Ĵ�С
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
	*	������
	*	s: SOCKET
	*	buf: ���͵��ֽڻ�����ָ��
	*	len: ���͵��ֽڳ���
	*	flags:	(�ɰ�λ��)
	*		0				
	*		MSG_DONTROUTE
	*		MSG_OOB(�������ݣ�����������)
	*
	*	���ط��ͳɹ�������
	*/
	size_t len = strlen(buf);
	size_t pos = 0;
	while(len > 0){
		error = send(sClient, &buf[pos], len, 0);
		len -= error;
		pos += error;
	}

	/*
	*	��ɶ���ǰ�������������֤���������շ����
	*	������
	*	how: 
	*		SD_SEND		ֹͣ����
	*		SD_RECEIVE	ֹͣ����
	*		SD_BOTH		���߶�ֹͣ
	*/
	shutdown(sClient,SD_BOTH);
	
	closesocket(sClient);

	error = WSACleanup(); //�ͷ���Դ����Ӧ WSAStartup ����
	if(error == SOCKET_ERROR){
		printf("WSACleanup Error! ErrorCode: %d \n", WSAGetLastError());
	}
	return 0;
}