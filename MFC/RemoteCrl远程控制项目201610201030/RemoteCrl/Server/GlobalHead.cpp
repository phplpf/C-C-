
#include "stdafx.h"
#include "GlobalHead.h"

//////////////////////////////////////////////////////////////////////
/////////һЩ��Ҫ��ϵͳ���///////////
HANDLE hOnlyInstance=NULL;	//	Ҫ��ֻ��һ��ʵ��
WSAEVENT hExitEvent=NULL;	//	�˳�ϵͳ�¼�
//////////////////////////////////////

/////////ϵͳ����/////////////////////
char szHostName[MAX_COMPUTERNAME_LENGTH + 1]; //��������
char szHostAddr[MAX_STRING_LEN];	//������ַ
int	 nHostPort=8111;	//�������˿ں�

DWORD SENDRECV_TIMEOUT=1200000;	//�շ�����ʱ��ʱ����

HANDLE hAcceptThread=NULL;	//���������߳̾��
HANDLE hCleanupThread=NULL;	//������Դ�߳̾��
UINT uAcceptThreadID=0;		//���������߳�IDֵ
UINT uCleanupThreadID=0;	//������Դ�߳�IDֵ
