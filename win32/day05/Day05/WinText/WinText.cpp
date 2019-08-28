#include <windows.h>
HINSTANCE g_hInstance = 0;
void OnPaint( HWND hWnd )
{
	PAINTSTRUCT ps = {0};
	HDC hdc = BeginPaint( hWnd, &ps );

	SetTextColor( hdc, RGB( 255, 0, 0 ) );      // �����ı���ɫ
	SetBkColor( hdc, RGB( 220, 200, 220 ) ); // ���ñ�����ɫ
	SetBkMode( hdc, TRANSPARENT );        // ���ñ���ģʽ( ��͸��/͸��) 

	// ��������
	HFONT hFont = CreateFont(30,0,100,0,900,0,1,1,GB2312_CHARSET,0,0,0,0,"LiSu");
	// ������Ӧ�õ�DC��
	HGDIOBJ hOldFont = SelectObject( hdc, hFont );
	char szText[] = "���пڴ��";
	// �����ַ���
	TextOut( hdc, 100, 100, szText, strlen(szText) );
	RECT rc = {0};	
	rc.left = 100;
	rc.top = 150;
	rc.right = 200;
	rc.bottom = 200;
//	Rectangle( hdc, 100,150,200,200);
	DrawText( hdc, szText, strlen(szText), &rc,
		DT_CENTER | DT_TOP | DT_SINGLELINE | DT_HIDEPREFIX | DT_NOCLIP);
	// ��DC��ȡ������
	SelectObject( hdc, hOldFont );
	// ��������
	DeleteObject( hFont );
	EndPaint( hWnd, &ps );
}
// 2. ���ڴ�����
LRESULT CALLBACK WndProc(HWND hWnd,UINT msgID,
	WPARAM wParam, LPARAM lParam)
{
	switch(msgID)
	{
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
	wndCls.hbrBackground = CreateSolidBrush( RGB( 200, 220, 220 ) );
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