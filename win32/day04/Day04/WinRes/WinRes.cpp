#include <windows.h>
#include "resource.h"
HINSTANCE g_hInstance = 0;
void OnPaint( HWND hWnd )
{
	PAINTSTRUCT ps = {0};
	HDC hdc = BeginPaint( hWnd, &ps );
	HICON hIcon = LoadIcon( g_hInstance, (LPCSTR)IDI_ICON1);
	DrawIcon(hdc, 100,100, hIcon );
	EndPaint( hWnd, &ps );
}
void OnCommand( HWND hWnd, WPARAM wParam )
{
	switch( LOWORD( wParam )) // ����ID
	{
	case ID_NEW:
		if( !HIWORD(wParam))
			MessageBox( hWnd, "�½��˵�����", "Infor", MB_OK );
		else
			MessageBox( hWnd, "Ctrl+N�����", "Infor", MB_OK );
		break;
	case ID_SET:
		MessageBox( hWnd, "Ctrl+S�����","Infor", MB_OK );
		break;
	}
}
// 2. ���ڴ�����
LRESULT CALLBACK WndProc(HWND hWnd,UINT msgID,
	WPARAM wParam, LPARAM lParam)
{
	switch(msgID)
	{
	case WM_COMMAND:
		OnCommand( hWnd, wParam );
		break;
	case WM_SETCURSOR:
		if( LOWORD(lParam)== HTCLIENT ){
			RECT rcClient = {0};
			GetClientRect( hWnd, &rcClient );
			POINT pt = {0};
			GetCursorPos(&pt);  // ��ȡ�������( ��Ļ����ϵ�� )
			ScreenToClient( hWnd, &pt );  // ��Ļ����ϵ  ---> �ͻ�������ϵ
			if( pt.x <= rcClient.right / 2  ){
			   HCURSOR hCur = LoadCursor( g_hInstance, (LPCSTR)IDC_CURSOR1);
			   SetCursor( hCur );
			}else{
			   HCURSOR hCur = LoadCursor( g_hInstance, (LPCSTR)IDC_CURSOR2);
			   SetCursor( hCur );
			}
			return 0;
		}
		break;
	case WM_PAINT:
		OnPaint( hWnd );
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
	wndCls.hCursor = LoadCursor( g_hInstance, (LPCSTR) IDC_CURSOR1 );
	wndCls.hIcon = NULL;//LoadIcon( g_hInstance, (LPCSTR)IDI_ICON1 );
	wndCls.hInstance = g_hInstance;
	wndCls.lpfnWndProc = wndProc;
	wndCls.lpszClassName = lpClassName;
	wndCls.lpszMenuName = (LPCSTR)IDR_MENU1;
	wndCls.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndCls);
}
// 4. ��������
HWND CreateMain( LPSTR lpClassName, LPSTR lpWndName){
	HWND hWnd = CreateWindowEx( 0, lpClassName, lpWndName,
		WS_OVERLAPPEDWINDOW, 100, 100, 700, 500,
		NULL, NULL, g_hInstance, NULL );
	HICON hIcon = LoadIcon( g_hInstance,(LPCSTR)IDI_ICON1);
	SendMessage(hWnd,WM_SETICON,ICON_BIG,(LPARAM)hIcon);
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
	HACCEL hAccel = LoadAccelerators( g_hInstance, (LPCSTR) IDR_ACCELERATOR1);
	while( GetMessage( &nMsg, NULL, 0, 0 ) )
	{
		if(!TranslateAccelerator( nMsg.hwnd, hAccel, &nMsg ))
		{
			TranslateMessage( &nMsg );
			DispatchMessage( &nMsg );
		}	
	}
}
// 1. ����WinMain����
int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPrevIns,
	LPSTR lpCmdLine,int nCmdShow){
		g_hInstance = hInstance;
		Register( "Main", WndProc);

		char szTitle[256] = {0};
		LoadString( g_hInstance, IDS_TITLE, szTitle, 256 );
		HWND hWnd = CreateMain( "Main", szTitle );

		Display( hWnd );
		Message();
		return 0;
}