#include <windows.h>
// 2. ���ڴ����� ( �Զ��壬������Ϣ )
LRESULT CALLBACK WndProc( HWND hWnd, UINT msgID,
	WPARAM wParam, LPARAM lParam )
{
	// 7. ��Ϣ����
	return DefWindowProc( hWnd,msgID, wParam, lParam);
	           // �Ը�����Ϣ��Ĭ�ϴ���
}
// 1. ����WinMain����
int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPrevIns,
	LPSTR lpCmdLine,int nCmdShow)
{
	// 3. ע�ᴰ����
	WNDCLASS wndCls = {0};
	wndCls.cbClsExtra = 0;			        // �����฽�����ݻ�����
	wndCls.cbWndExtra = 0;                // ���ڸ������ݻ�����
	wndCls.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // ����ɫ
	wndCls.hCursor = NULL;			        // ��� NULL��ʾʹ��ϵͳĬ��ֵ
	wndCls.hIcon = NULL;				    // ͼ�� NULL��ʾʹ��ϵͳĬ��ֵ
	wndCls.hInstance = hInstance;      // WinMain�ĵ�һ������
	wndCls.lpfnWndProc = WndProc; // ���ڴ������ĺ���ָ�������
	wndCls.lpszClassName = "Main";  // ����������
	wndCls.lpszMenuName = NULL;   // �˵�  NULL��ʾû�в˵�
	wndCls.style = CS_HREDRAW | CS_VREDRAW; // ��������
	RegisterClass(&wndCls);    // �����ϸ�ֵд�����ϵͳ
	// 4. ��������
	HWND hWnd = CreateWindow("Main","Window",WS_OVERLAPPEDWINDOW,
		100,100,700,500,NULL,NULL,hInstance,NULL);
	// 5. ��ʾ����
	ShowWindow( hWnd, SW_SHOW);
	// 6. ��Ϣѭ��
	MSG nMsg = {0};
	while(GetMessage(&nMsg,NULL,0,0))
	{
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);
	}
	return 0;
}