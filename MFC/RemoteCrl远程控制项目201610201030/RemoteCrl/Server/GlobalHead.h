#pragma once

/////////////////����ȫ�ֱ���//////////////////
#define MAX_STRING_LEN 50
#define PEER_WAITTIME 60000	//��ʱ�趨ʱ��
#define PEER_KILLTHREADTIME 5000
#define PEER_CLEANTHREADTIME 200	//��ʱ�趨ʱ��
#define PEER_FUNERROR 4116010325
extern DWORD SENDRECV_TIMEOUT;		//�շ�����ʱ��ʱ����

// ȫ��ʵ�������������
extern HINSTANCE hInst;							
extern HWND		 hMainWnd;

/////////һЩ��Ҫ��ϵͳ���///////////
extern HANDLE hOnlyInstance;	//	Ҫ��ֻ��һ��ʵ��
extern HANDLE hExitEvent;		//	�˳�ϵͳ�¼�
//////////////////////////////////////
/////////ϵͳ����/////////////////////
extern char szHostName[MAX_COMPUTERNAME_LENGTH + 1]; //��������
extern char szHostAddr[MAX_STRING_LEN];	//������ַ
extern int	nHostPort;	//�������˿ں�

extern HANDLE hAcceptThread;	//���������߳̾��
extern HANDLE hCleanupThread;	//������Դ�߳̾��
extern UINT uAcceptThreadID;	//���������߳�IDֵ
extern UINT uCleanupThreadID;	//������Դ�߳�IDֵ
extern UINT nThread;
//////////////////////////////////////