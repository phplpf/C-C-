#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

void TCPServer()
{
	// 1 ����
	SOCKET hSockSvr=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (hSockSvr==INVALID_SOCKET)return;
	// 2 ��
	SOCKADDR_IN addrSvr={0};
	addrSvr.sin_family=AF_INET;
	addrSvr.sin_port=htons(5678);
	addrSvr.sin_addr.S_un.S_addr=INADDR_ANY;
	bind(hSockSvr,(SOCKADDR*)&addrSvr,sizeof(addrSvr));
	// 3 ����
	listen(hSockSvr,5);
	// 4 ���տͻ�������
	SOCKADDR_IN addrClient={0};
	int nLen= sizeof(addrClient);
	printf("�ȴ��ͻ�������...\n");
	SOCKET hSockClient = accept(hSockSvr,(SOCKADDR*)&addrClient,&nLen);
	printf("�Ѿ���ͻ��˽������ӡ�\n");
	// 5 ͨ��
	// 5.1 �����������Ƚ�������
	char szBuff[256]={0};
	int nRecv = recv(hSockClient,szBuff,256,0);
	char * IP= inet_ntoa(addrClient.sin_addr);
	printf("%s:%s,%d\n",IP,szBuff,nRecv);
	// 5.2 Ȼ���ٰ�����ԭ�����ͻؿͻ���
	send(hSockClient,szBuff,strlen(szBuff),0);
	// 6 �ر�
	closesocket(hSockClient);
	closesocket(hSockSvr);
	getchar();
}
void UDPServer()
{
	// 1 ����
	SOCKET hSockSvr=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (hSockSvr == INVALID_SOCKET)return;
	// 2 ��
	SOCKADDR_IN addrSvr={0};
	addrSvr.sin_family = AF_INET;
	addrSvr.sin_port = htons(5678);
	addrSvr.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(hSockSvr,(SOCKADDR*)&addrSvr,sizeof(addrSvr));
	// 3 ͨ��
	// 3.1 ��������
	char szBuff[256]={0};
	SOCKADDR_IN addrClient={0};
	int nLen=sizeof(addrClient);
	int nRecv = recvfrom(hSockSvr,szBuff,256,0,(SOCKADDR*)&addrClient,&nLen);
	char *IP=inet_ntoa(addrClient.sin_addr);
	printf("%s,%s,%d\n",IP,szBuff,nRecv);
	// 3.2 ������ԭ�����ͻؿͻ���
	sendto(hSockSvr,szBuff,strlen(szBuff),0,(SOCKADDR*)&addrClient,nLen);
	// 4 �ر�
	closesocket(hSockSvr);
	getchar();
		

}
int main()
{
	// 1 ��ʼ��socket��
	WSAData ws={0};
	WSAStartup(MAKEWORD(2,2),&ws);
	// 2 ͨ��
	//TCPServer();
	UDPServer();
	// 3 ж��
	WSACleanup();
	return 0;
}