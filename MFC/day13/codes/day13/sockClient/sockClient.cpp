#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

void TCPClient()
{
	// 1 ����
	SOCKET hSockClient=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (hSockClient==INVALID_SOCKET)return;
    // 2 ����
	SOCKADDR_IN addrSvr={0};
	addrSvr.sin_family=AF_INET;
	addrSvr.sin_port=htons(5678);
	addrSvr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
    connect(hSockClient,(SOCKADDR*)&addrSvr,sizeof(addrSvr));
	// 3 ͨ��
	// 3.1 ���ȷ�������
	char *szSend="hello world";
	send(hSockClient,szSend,strlen(szSend),0);
	// 3.2 Ȼ���������
	char szBuff[256]={0};
	int nRecv = recv(hSockClient,szBuff,256,0);
	printf("%s,%d\n",szBuff,nRecv);
	// 4 �ر�
	closesocket(hSockClient);
	getchar();
}
void UDPClient()
{
	// 1 ����
	SOCKET hSockClient=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (hSockClient==INVALID_SOCKET)return;
	// 2 ͨ��
	// 2.1 ���ȷ�������
	SOCKADDR_IN addrSvr={0};
	addrSvr.sin_family = AF_INET;
	addrSvr.sin_port = htons(5678);
	addrSvr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	char szSend[]="Hello World";
	sendto(hSockClient,szSend,strlen(szSend),0,(SOCKADDR*)&addrSvr,
		sizeof(addrSvr));
	// 2.2 Ȼ���������
	char szBuff[256]={0};
	int nLen=sizeof(addrSvr);
	int nRecv = recvfrom(hSockClient,szBuff,256,0,(SOCKADDR*)&addrSvr,&nLen);
	printf("%s,%d\n",szBuff,nRecv);
	// 3 �ر�
	closesocket(hSockClient);
	getchar();
}
int main()
{
	// 1 ��ʼ��socket��
	WSAData ws={0};
	WSAStartup(MAKEWORD(2,2),&ws);
	// 2 ͨ��
	//TCPClient();
	UDPClient();
	// 3 ж��
	WSACleanup();
	return 0;
}