#pragma once
#include <process.h>
#include "command.h"//��װͨ��ʱ�Ľṹ��

/////////////////////////////////////////////////////
#define CUR_THREADID GetCurrentThreadId()

typedef unsigned (__stdcall *PTHREAD_START)(void*);
//���崴���̺߳���,�Լ򻯴������д
#define BeginPeerThread(pfnStartAddr,pvParam,pdwThreadID)\
		((HANDLE)(_beginthreadex((void*)NULL,\
                                 0,\
								 (PTHREAD_START)(pfnStartAddr),\
								 (void*)(pvParam),\
								 0,\
								 (unsigned*)(pdwThreadID)\
								)\
                 )\
		)

#define EndPeerThread(retVal) _endendthreadex((unsigned)retVal)
///////////////////////////////////////////////////////

typedef struct tagConnectThread
{
	HANDLE			hThread;	//�߳̾��
	UINT			threadID;	//�߳�ID
}CONNECTTHREAD;

typedef struct tagConnectSocket
{
	SOCKET			socket;		//����Socket
	char			IP[64];		//IP��ַ,Ϊ�˼���IP6
}CONNECTSOCKET;


//�û�list����ʱʹ�õıȽϺ���
struct IDCompare:binary_function<CONNECTTHREAD,unsigned int, bool>
{
	bool operator()(const CONNECTTHREAD& _X, const unsigned int& _Y) const
	{
		return (_X.threadID == _Y); 
	}
};

typedef list<CONNECTTHREAD>	CONNECTTHREADLIST;	//�ͻ������߳��б�
typedef list<HANDLE>	UNUSEDTHREADLIST;	//���õ��߳̾���б�

UINT WINAPI AcceptThread(PVOID pParam);
UINT WINAPI ServerThread(PVOID pParam);
UINT WINAPI CleanupThread(PVOID pParam);

////////////////////////////////////////////
extern CONNECTTHREADLIST	listConnectThread;	//�ͻ������߳��б�
extern UNUSEDTHREADLIST		listUnusedThread;	//���õ��߳̾���б�
extern CRITICAL_SECTION		csProtectList;		//ֻ����һ���̷߳�����Щ�б�
//////////////////////////////////////////
void DeleteThread(DWORD dwThreadID);