#include <windows.h>
HINSTANCE g_hInstance = 0;  // Ӧ�ó����ʵ�����
void SysReg()
{
	// ϵͳ��������ϵͳע�ᣬӦ�ó������ֱ��ʹ��
	// ��������
	HWND hWnd = CreateWindow("BUTTON","OK",WS_OVERLAPPEDWINDOW,
		100,100,700,500,NULL,NULL, g_hInstance, NULL);
	// ��ʾ����
	ShowWindow( hWnd, SW_SHOW);
	// ��Ϣѭ��
	MSG nMsg = {0};
	while( GetMessage( &nMsg, NULL, 0, 0 ) )
	{
		// ������Ϣ
		TranslateMessage( &nMsg );
		// �ɷ���Ϣ
		DispatchMessage( &nMsg );
	}
}
void AppReg()
{
	WNDCLASS wndCls = {0};
	wndCls.cbClsExtra = 0;
	wndCls.cbWndExtra = 0;
	wndCls.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndCls.hCursor = NULL;
	wndCls.hIcon = NULL;
	wndCls.hInstance = g_hInstance;              /******************/
	wndCls.lpfnWndProc = DefWindowProc;
	wndCls.lpszClassName = "Main";                /*****************/
	wndCls.lpszMenuName = NULL;
	wndCls.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndCls);
	HWND hWnd = CreateWindow("Main", "Window", WS_OVERLAPPEDWINDOW,
		100,100,700,500,NULL,NULL,g_hInstance,NULL);
}
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevIns,
	LPSTR lpCmdLine, int nCmdShow)
{
	g_hInstance = hInstance;
//	SysReg();
	AppReg();
	return 0;
}