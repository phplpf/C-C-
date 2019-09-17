// ServerSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCServer.h"
#include "ServerSocket.h"


// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// 1 ��ʼ��������(�������󶨺ͼ���)
BOOL CServerSocket::InitServer(UINT nPort)
{
	// 1 2 ��������
	if (!Create(nPort))
	{
		return FALSE;
	}
	// 3 ����
	return Listen();
}
// CServerSocket ��Ա����

typedef struct _tagHeader{
	char szName[256];//�ļ�����
	long nLen;//�ļ�����
}HEADER,*LPHEADER;
BOOL CServerSocket::RecvData(CSocket& client,BYTE* pData,long nLen)
{
	long nLeft = nLen;//ʣ��Ļ�û�н��յ����ݵĳ���
	BYTE* pTmpData=pData;//��ʱ��ָ��
	while ( nLeft > 0 )
	{
		int nRecv = client.Receive(pTmpData,nLeft);
		if (nRecv==SOCKET_ERROR)
		{
			return FALSE;
		}
		nLeft = nLeft-nRecv;
		pTmpData = pTmpData+nRecv;
	}
	return TRUE;
	
}
void CServerSocket::OnAccept(int nErrorCode)

{
	// 4 ���տͻ�������
	CSocket client;
	Accept(client);
	// 5 ͨ��(�����ļ�)
	// 5.1 �Ƚ����ļ���Ϣ(�ļ����Ⱥ��ļ�������)
	HEADER header={0};
	RecvData(client,(BYTE*)&header,sizeof(header));
	// 5.2 Ȼ���ٽ����ļ�����
	BYTE* pData=(BYTE*)malloc(header.nLen);
	RecvData(client,pData,header.nLen);
	// 5.3 ��󣬽��ļ����浽������
	CFile file;
	CString strPath="d:/";
	strPath+=header.szName;
	file.Open(strPath,CFile::modeCreate|CFile::modeWrite);
	file.Write(pData,header.nLen);
	file.Close();
	free(pData);
	// 6 �ر��׽���
	client.Close();
	CSocket::OnAccept(nErrorCode);
}
