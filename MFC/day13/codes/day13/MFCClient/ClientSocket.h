#pragma once

// CClientSocket ����Ŀ��

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
	// 1 ��ʼ���ͻ���(���ӷ�����)
	BOOL InitClient(char* IP,UINT nPort);
	// 2 �����ļ�
	BOOL SendFile(CString strPath);
	// 3 ��������
	BOOL SendData(BYTE* pData,long nLen);
};


