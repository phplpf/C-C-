// ������Ϣ
#define  WM_MYMESSAGE  WM_USER + 1001
#include <windows.h>
#include <stdio.h>
HINSTANCE g_hInstance = 0;
void OnCreate( HWND hWnd ){
	// �����Զ�����Ϣ  �Զ�����Ϣ�ķ��Ϳ���������λ��( ���ڴ����ɹ�֮��)
	// �ȿ���ʹ��SendMessage��Ҳ����ʹ��PostMessage
//	SendMessage( hWnd, WM_MYMESSAGE, 100, 200 );
	PostMessage( hWnd, WM_MYMESSAGE, 100, 200 );
}
// �����Զ�����Ϣ
void OnMyMessage( HWND hWnd, WPARAM wParam, LPARAM lParam){
	char szText[256] = { 0 };
	sprintf( szText," �Զ�����Ϣ������: wParam:%d, lParam:%d \n",wParam,lParam);
	MessageBox( hWnd,szText,"Infor",MB_OK);
}
// 2. ���ڴ�����
LRESULT CALLBACK WndProc(HWND hWnd,UINT msgID,
	WPARAM wParam, LPARAM lParam){
	switch(msgID){
	case WM_MYMESSAGE:
		OnMyMessage( hWnd, wParam, lParam);
		break;
	case WM_CREATE:
		OnCreate( hWnd );
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
	wndCls.lpszMenuName = NULL;
	wndCls.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndCls);
}
// 4. ��������
HWND CreateMain( LPSTR lpClassName, LPSTR lpWndName){
	HWND hWnd = CreateWindowEx( 0, lpClassName, lpWndName,
		WS_OVERLAPPEDWINDOW, 100, 100, 700, 500,
		NULL, NULL, g_hInstance, NULL );
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
		g_hInstance = hInstance;
		Register( "Main", WndProc);
		HWND hWnd = CreateMain( "Main", "Window" );
		Display( hWnd );
		Message();
		return 0;
}