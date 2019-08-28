#include <windows.h>
#include <stdio.h>
HINSTANCE g_hInstance = 0;
HANDLE g_hOutput = 0;  // ���ձ�׼������
HWND g_hEdit = 0;   // �༭�򴰿ھ��
/*void OnCreate( HWND hWnd, LPARAM lParam)
{
	CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
	char* pszText =(char*) pcs->lpCreateParams;
	MessageBox( hWnd, pszText, "Infor", MB_OK );
}*/
void OnCreate( HWND hWnd)
{
	g_hEdit = CreateWindowEx( 0, "EDIT", "Hello", WS_CHILD | WS_VISIBLE | WS_BORDER,
		0,0,200,200, hWnd, NULL, g_hInstance, NULL);
}
void OnSize( HWND hWnd, LPARAM lParam)
{
	WORD nWidth = LOWORD( lParam );
	WORD nHeight = HIWORD( lParam );

	MoveWindow( g_hEdit, 0, 0, nWidth, nHeight, TRUE );

	char szText[256] = {0};
	sprintf( szText, "WM_SIZE --- ��%d,��:%d\n", nWidth, nHeight );
	WriteConsole( g_hOutput, szText, strlen(szText), NULL, NULL );
}
// 2. ���ڴ�����
LRESULT CALLBACK WndProc(HWND hWnd,UINT msgID,
	WPARAM wParam, LPARAM lParam)
{
	switch(msgID)
	{
	case WM_SIZE:
		OnSize( hWnd, lParam );
		break;
	case WM_CREATE:
//		OnCreate( hWnd, lParam );
		OnCreate( hWnd );
		break;
	case WM_SYSCOMMAND:
//		return 0;
//		MessageBox( hWnd, "WM_SYSCOMMAND", "Infor", 
//			MB_OK | MB_ICONINFORMATION );
		if( wParam == SC_CLOSE){
			int nRet = MessageBox( hWnd, "�Ƿ��˳�?", "Infor",
				        MB_YESNO | MB_ICONINFORMATION);
			if( nRet == IDYES ){
				// ʲôҲ��д
			}else{
				return 0;
			}
		}
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
	char * pszText = "Hello Data";
	HWND hWnd = CreateWindowEx( 0, lpClassName, lpWndName,
		WS_OVERLAPPEDWINDOW, 200, 200, 500, 400,
		NULL, NULL, g_hInstance, pszText );
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
/*	while( GetMessage( &nMsg, NULL, 0, 0 ) ){
		TranslateMessage( &nMsg );
		DispatchMessage( &nMsg );
	}*/

	while(1){
		if(PeekMessage(&nMsg, NULL, 0, 0, PM_NOREMOVE ))
		{
			// ����Ϣ
			if( GetMessage( &nMsg, NULL, 0, 0)) // ���� WM_QUIT
			{
				 TranslateMessage( &nMsg );
				 DispatchMessage( &nMsg );
			}else{ // WM_QUIT
				return;
			}
		}else{ // û����Ϣ
			// ���д���
			WriteConsole( g_hOutput, "OnIdle", 6, NULL,NULL);
		}
	}

}
// 1. ����WinMain����
int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPrevIns,
	LPSTR lpCmdLine,int nCmdShow){
		AllocConsole();  // ����һ��DOS����
		g_hOutput = GetStdHandle( STD_OUTPUT_HANDLE );
		g_hInstance = hInstance;
		Register( "Main", WndProc);
		HWND hWnd = CreateMain( "Main", "Window" );
		Display( hWnd );
		Message();
		return 0;
}