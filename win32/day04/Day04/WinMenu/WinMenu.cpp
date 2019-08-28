#include <windows.h>
#include <stdio.h>
#include "resource.h"
HINSTANCE g_hInstance = 0;
HMENU g_hMenu = 0;   // ����˵��ľ��
HMENU g_hFile = 0;  // �Ӳ˵����
int g_state = 0;  // ��־��ѡ״̬
HANDLE g_hOutput = 0;
void OnCommand( HWND hWnd, WPARAM wParam )
{
	switch( LOWORD( wParam))  // ������Ĳ˵����ID
	{
	case ID_POPUP_CUT:
		MessageBox( hWnd, "���в˵�����","Infor",MB_OK);
		break;
	case ID_NEW:
//		MessageBox( hWnd,  "�½��˵�����", "Infor", MB_OK );
		if( !g_state )
			CheckMenuItem( g_hFile, ID_NEW, MF_BYCOMMAND|MF_UNCHECKED);
		else
			CheckMenuItem( g_hFile, 0, MF_BYPOSITION | MF_CHECKED );
		g_state = !g_state;
		break;
	case ID_EXIT:
		PostMessage( hWnd, WM_QUIT, 0, 0 );
		break;
	case ID_ABOUT:
		MessageBox( hWnd, "���ڲ˵�����", "Infor", MB_OK );
		break;
	}
}
void OnInitMenuPopup( HWND hWnd, WPARAM wParam, LPARAM lParam )
{
	char szText[256] = {0};
	sprintf( szText, "������ʾ�Ĳ˵����:%d,������Ĳ˵�������:%d,"
		"������ʾ�Ĳ˵��Ƿ��Ǵ��ڲ˵�:%d\n",
		wParam, LOWORD( lParam ), HIWORD( lParam ));
	WriteConsole( g_hOutput, szText, strlen(szText), NULL, NULL );
}
void OnRButtonUp( HWND hWnd, LPARAM lParam )
{
	HMENU hMenu = LoadMenu( g_hInstance, (LPCSTR) IDR_MENU2 );
	HMENU hPopup = GetSubMenu( hMenu, 0 );
	POINT pt = {0};
	pt.x = LOWORD(lParam);
	pt.y = HIWORD(lParam);
	ClientToScreen( hWnd, &pt );
	BOOL nRet = TrackPopupMenu( hPopup, 
		TPM_CENTERALIGN | TPM_VCENTERALIGN | TPM_RETURNCMD,
		pt.x,pt.y,0,hWnd,NULL);
	switch( nRet ){
	case ID_POPUP_CUT:
		MessageBox( hWnd, "û�з���WM_COMMAND��Ϣ�����в˵�����������",
			  "Infor",MB_OK);
		break;
	}
}
void OnContextMenu( HWND hWnd, LPARAM lParam )
{
	HMENU hMenu = LoadMenu( g_hInstance, (LPCSTR) IDR_MENU2 );
	HMENU hPopup = GetSubMenu( hMenu, 0 );
	POINT pt = {0};
	pt.x = LOWORD(lParam);
	pt.y = HIWORD(lParam);
//	ClientToScreen( hWnd, &pt );
	BOOL nRet = TrackPopupMenu( hPopup, 
		TPM_CENTERALIGN | TPM_VCENTERALIGN | TPM_RETURNCMD,
		pt.x,pt.y,0,hWnd,NULL);
	switch( nRet ){
	case ID_POPUP_CUT:
		MessageBox( hWnd, "û�з���WM_COMMAND��Ϣ�����в˵�����������",
			"Infor",MB_OK);
		break;
	}
}
// 2. ���ڴ�����
LRESULT CALLBACK WndProc(HWND hWnd,UINT msgID,
	WPARAM wParam, LPARAM lParam)
{
	switch(msgID)
	{
	case WM_CONTEXTMENU:
		OnContextMenu( hWnd, lParam );
		break;
	case WM_RBUTTONUP:
//		OnRButtonUp( hWnd, lParam );
		break;
	case WM_INITMENUPOPUP:
		OnInitMenuPopup( hWnd, wParam, lParam );
		break;
	case WM_COMMAND:
		OnCommand( hWnd, wParam );
		break;
	case WM_DESTROY:
		PostQuitMessage( 0 );   // GetMessage����0 ?
		break;
	}
	return DefWindowProc( hWnd, msgID, wParam, lParam);
}
// 3. ע�ᴰ����
void Register( LPSTR  lpClassName, WNDPROC wndProc )
{
	WNDCLASS wndCls = {0};
	wndCls.cbClsExtra = 0;
	wndCls.cbWndExtra = 0;
	wndCls.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndCls.hCursor = NULL;
	wndCls.hIcon = NULL;
	wndCls.hInstance = g_hInstance;
	wndCls.lpfnWndProc = wndProc;
	wndCls.lpszClassName = lpClassName;
	wndCls.lpszMenuName = NULL;  //(LPCSTR) IDR_MENU1;
	wndCls.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndCls);
}
// 4. ��������
HWND CreateMain( LPSTR lpClassName, LPSTR lpWndName){
	g_hMenu = LoadMenu( g_hInstance, (LPCSTR)IDR_MENU1);
	g_hFile = GetSubMenu( g_hMenu, 0 );

	HWND hWnd = CreateWindowEx( 0, lpClassName, lpWndName,
		WS_OVERLAPPEDWINDOW, 100, 100, 700, 500,
		NULL, g_hMenu, g_hInstance, NULL );
//	SetMenu( hWnd, hMenu );
	return hWnd;
}
// 5. ��ʾ����
void Display( HWND hWnd ){
	ShowWindow( hWnd, SW_SHOW );
	UpdateWindow( hWnd );
}
// 6. ��Ϣѭ��
void Message(){
	MSG nMsg = {0};
	while( GetMessage( &nMsg, NULL, 0, 0 ) ){
		TranslateMessage( &nMsg );
		DispatchMessage( &nMsg );
	}
}
// 1. ����WinMain����
int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPrevIns,
	LPSTR lpCmdLine,int nCmdShow){
		AllocConsole();
		g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE );
		g_hInstance = hInstance;
		Register( "Main", WndProc);
		HWND hWnd = CreateMain( "Main", "Window" );
		Display( hWnd );
		Message();
		return 0;
}