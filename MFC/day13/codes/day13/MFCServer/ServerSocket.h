#pragma once

// CServerSocket ����Ŀ��

class CServerSocket : public CSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();
    // 1 ��ʼ��������
	BOOL InitServer(UINT nPort);
	// 2 �����ļ�(�ŵ��¼���������)
	virtual void OnAccept(int nErrorCode);
	// 3 ��������
	BOOL RecvData(CSocket& client,BYTE* pData,long nLen);
	
};


