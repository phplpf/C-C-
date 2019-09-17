// PeerThread.cpp: implementation of the PeerThread.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PeerThread.h"
#include "globalhead.h"
#include "peersocket.h"
#include "CaptureScreen.h"

#include "command.h"
#include "screenctrl.h"

//////////////////////////////////////////////////////////////////////
CONNECTTHREADLIST	listConnectThread;	//�ͻ������߳��б�
UNUSEDTHREADLIST	listUnusedThread;	//���õ��߳̾���б�
CRITICAL_SECTION	csProtectList;		//ֻ����ͬʱһ���̷߳�����Щ�б�
///////////////////////////////
//����Զ�����ӵ��߳�
UINT WINAPI AcceptThread(PVOID pParam)
{
	CONNECTTHREAD connectthread;
	HANDLE hNewThread;
	DWORD  dwNewThreadID;
	SOCKET s; 
	SOCKADDR_IN ClientAddr;
	SOCKADDR_IN ClientAddrIn;
	int iAddrLen = sizeof(ClientAddr);
	CONNECTSOCKET ConnectSocketInfo;

	if(!PeerCreateSocket(&s,PEER_STREAM))
	{
		return -1;
	}
	if(!PeerBindSocket(s,szHostAddr,nHostPort))
	{
		PeerCloseSocket(s);
		return -1;
	}
	if(!PeerListenSocket(s))
	{
		PeerCloseSocket(s);
		return -1;
	}

	for(;;)
	{
			SOCKET ClientSocket;
			if(	!PeerAcceptSocket( &ClientSocket, &ClientAddr, s ))
			{
				continue; 
			}
			else
			{
				memcpy(&ClientAddrIn,&ClientAddr,sizeof(SOCKADDR_IN));//��ַ
				strcpy(ConnectSocketInfo.IP,inet_ntoa(ClientAddrIn.sin_addr));//IP��ַ
				ConnectSocketInfo.socket=ClientSocket;//socket���
				//�����µķ����߳�
				if((hNewThread=BeginPeerThread(ServerThread,&ConnectSocketInfo,&dwNewThreadID))==NULL)
					continue;
				else
				{
					connectthread.hThread=hNewThread;
					connectthread.threadID=dwNewThreadID;
					EnterCriticalSection(&csProtectList);
					listConnectThread.push_back(connectthread);//���������߳���Ϣ���浽������
					LeaveCriticalSection(&csProtectList);
				}
			}
		
	}
	PeerCloseSocket(s);
	return 0;
}
/////////////////////////////////
//�����߳�
/////////////////////////////////
UINT WINAPI ServerThread(PVOID pParam)
{
	/////�õ����ӵ�socket//////
	CONNECTSOCKET SocketInfo;
	SocketInfo=*(CONNECTSOCKET*)pParam;
	SOCKET s;
	s=SocketInfo.socket;

	DWORD retLen; //�������ݳ���
	COMMAND command;//����ͷ
	
	///////////////////////////////////

	memset((char*)&command,0,sizeof(COMMAND));
	if(!PeerRecvDataS(s,(char*)&command,sizeof(command),&retLen))
	{
		PeerCloseSocket(s);
		DeleteThread(CUR_THREADID);
		return 0;
	}
	switch(command.CommandID)
	{
		case PEER_KEYMOUSE:
			PeerScreenMouseKey(s);
			break;
		case PEER_SCREEN_GET:
			PeerScreenGet(s);
			CleanScreenInfo();
			break;

	}
	PeerShutDownSocket(s);
	PeerCloseSocket(s);
	DeleteThread(CUR_THREADID);
	return 0;
}

/////////////////////////////
//�����Ѿ���ɲ������̵߳��߳�
UINT WINAPI CleanupThread(PVOID pParam)
{
	UNUSEDTHREADLIST::iterator it;
	for(;;)
	{
		if(WaitForSingleObject(hExitEvent, PEER_CLEANTHREADTIME)==WAIT_TIMEOUT)
		{
			EnterCriticalSection(&csProtectList);
			while(listUnusedThread.size())
			{	
				HANDLE h = listUnusedThread.front(); 
				DWORD n = WaitForSingleObject(h,PEER_KILLTHREADTIME);
				if(n==WAIT_TIMEOUT)
				{
					TerminateThread(h,0);
				}
				CloseHandle(h);
				listUnusedThread.pop_front();
			}
			LeaveCriticalSection(&csProtectList);
		}
		else
			return 0;
	}
	return 0;
}
///////////////////////////
///ɾ���Ѿ�ִ������߳̾��
void DeleteThread(DWORD dwThreadID)
{
	CONNECTTHREADLIST::iterator it;
	it=find_if(listConnectThread.begin(),listConnectThread.end(),bind2nd(IDCompare(),dwThreadID));
	if(it!=listConnectThread.end())
	{
		EnterCriticalSection(&csProtectList);
		listUnusedThread.push_back((*it).hThread);
		listConnectThread.erase(it);
		LeaveCriticalSection(&csProtectList);
	}
}
////////////////////////////////////////////////////////////

