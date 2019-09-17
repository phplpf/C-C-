// Server.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Server.h"
#include "globalhead.h"
#include "CaptureScreen.h"
#include "PeerSocket.h"
#include "PeerThread.h"
#include "command.h"
#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


HWND	  hMainWnd;//����ܴ��ھ��
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	
	//	1 ����������,��ֻ֤��һ��ʵ��		
	if ((hOnlyInstance=CreateMutex(NULL,false,"JFY's PeerYou"))==NULL)
		return -1;
	else if (GetLastError()==ERROR_ALREADY_EXISTS)
		return -1;


	//	2 ���������˳�������¼����
	if ((hExitEvent=WSACreateEvent())==WSA_INVALID_EVENT){
		CloseHandle(hOnlyInstance);
		return -1;
	}
	//	3 ��ʼ��socket��
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2,2),&wsaData)!=0) {
		//	�޿���WinSock DLL. 
		CloseHandle(hOnlyInstance);
		CloseHandle(hExitEvent);
		return -1;
	}
	
	
	
	
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SERVER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SERVER));


	InitializeCriticalSection(&csCaptureScreen);
	// ����Ϣѭ��:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	CloseHandle(hOnlyInstance);
	WSACloseEvent(hExitEvent);
	DeleteCriticalSection(&csCaptureScreen);
	WSACleanup();
	return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SERVER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SERVER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
       CloseHandle(hOnlyInstance);
	   WSACloseEvent(hExitEvent);
	   WSACleanup();
	   return FALSE;
   }
   hMainWnd=hWnd;
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_CREATE:
		//�õ���������
		int nComputerNameLen;
		nComputerNameLen=MAX_COMPUTERNAME_LENGTH + 1;
		if(SOCKET_ERROR==gethostname(szHostName,nComputerNameLen))
			return -1;
	
		//�õ�����IP��ַ
		HOSTENT *hentThisHost;
		hentThisHost=NULL;
		if(!(hentThisHost=gethostbyname(szHostName)))
			return -1;
		in_addr inaddrThisHost;
		memcpy(&inaddrThisHost.S_un.S_addr,hentThisHost->h_addr,hentThisHost->h_length);
		strcpy(szHostAddr,inet_ntoa(inaddrThisHost));

		
		//��ʼ���ؼ������(�����߳��б�)
		InitializeCriticalSection(&csProtectList);
		//���������߳�
		hAcceptThread=BeginPeerThread(AcceptThread,NULL,&uAcceptThreadID);
		if(!hAcceptThread)
		{
			return FALSE;
		}
		//���������̶߳�̬����ϵͳ
		hCleanupThread =BeginPeerThread(CleanupThread,NULL,&uCleanupThreadID);
		if(!hCleanupThread)
		{
			return FALSE;
		}
		
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		RECT rect;
		GetClientRect(hMainWnd,&rect);
		DrawText(hdc,szHostName,strlen(szHostName),&rect,DT_CENTER);
		DrawText(hdc,szHostAddr,strlen(szHostAddr),&rect,DT_SINGLELINE|DT_VCENTER|DT_CENTER);
		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE:
		
		HANDLE hEvent[2];
	    //�ȴ�������Ҫ�߳��Ƿ��Ѿ��˳�
		hEvent[0]=hAcceptThread;
		hEvent[1]=hCleanupThread;
		//�ر��߳̾��
		CloseHandle(hAcceptThread);
		CloseHandle(hCleanupThread);
		//���з����̶߳��Ѿ��˳�
		while(listConnectThread.size())
		{
			Sleep(100);
		}
		//ɾ���ٽ���(�����߳��б�)
		DeleteCriticalSection(&csProtectList);
		
		//���͹رմ�����Ϣ
		SendMessage(hMainWnd,WM_DESTROY,0,0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
