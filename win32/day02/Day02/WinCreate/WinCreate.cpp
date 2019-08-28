#include <windows.h>
HINSTANCE g_hInstance = 0;
// 2. ���ڴ�����
LRESULT CALLBACK WndProc(HWND hWnd,UINT msgID,
	WPARAM wParam, LPARAM lParam)
{
	switch(msgID)
	{
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
// �����Ӵ���
HWND CreateChild( LPSTR lpClassName, LPSTR lpWndName, HWND hParent)
{
	HWND hChild = CreateWindowEx(0,lpClassName,lpWndName,
		WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE,
		0,0,200,200, hParent, NULL, g_hInstance, NULL);
	return hChild;
}
// 1. ����WinMain����
int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPrevIns,
	LPSTR lpCmdLine,int nCmdShow){
	g_hInstance = hInstance;
	Register( "Main", WndProc);
	HWND hWnd = CreateMain( "Main", "Window" );
	Display( hWnd );
	Register( "Child", DefWindowProc);
	HWND hChild1 =  CreateChild( "Child", "c1",  hWnd);
	HWND hChild2 = CreateChild( "Child", "c2",  hWnd);
	MoveWindow( hChild1, 100, 100, 200, 200, TRUE );
	MoveWindow( hChild2, 400, 100, 200, 200, TRUE );
	Message();
	return 0;
}