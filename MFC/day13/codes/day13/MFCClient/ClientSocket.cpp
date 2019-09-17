// ClientSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCClient.h"
#include "ClientSocket.h"


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket ��Ա����
// 1 ��ʼ���ͻ���(���ӷ�����)
BOOL CClientSocket::InitClient(char* IP,UINT nPort)
{
	if (!Create())
	{
		return FALSE;
	}
	return Connect(IP,nPort);
}

typedef struct _tagHeader{
	char szName[256];//�ļ�����
	long nLen;//�ļ�����
}HEADER,*LPHEADER;

// 2 �����ļ�
BOOL CClientSocket::SendFile(CString strPath)
{
    // 1 ��ȡ�ļ�
	CFile file;
	file.Open(strPath,CFile::modeRead);
	CString strName=file.GetFileName();
	long nLen=file.GetLength();
	// 2 �����ļ���Ϣ
	HEADER header={0};
	header.nLen = nLen;
	strcpy(header.szName,strName);
	SendData((BYTE*)&header,sizeof(header));
	// 3 �����ļ�����
	BYTE* pData=(BYTE*)malloc(nLen);
	file.Read(pData,nLen);
	SendData(pData,nLen);
	file.Close();
	free(pData);
	// 4 �ر�socket
	Close();
	return TRUE;
}
// 3 ��������
BOOL CClientSocket::SendData(BYTE* pData,long nLen)
{
	BYTE* pTmpData = pData;
	long nLeft = nLen;
	while(nLeft>0)
	{
		int nSend=Send(pTmpData,nLeft);
		if (nSend == SOCKET_ERROR)
		{
			return FALSE;
		}
		nLeft -= nSend;
		pTmpData+=nSend;
	}
	return TRUE;
}