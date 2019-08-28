#include <windows.h>
#include "resource.h"
HINSTANCE g_hInstance = 0;
void DrawLine( HDC hdc ){
	MoveToEx( hdc, 100, 100, NULL );
	LineTo( hdc, 300, 300 );
	LineTo( hdc, 100, 300 );
	LineTo ( hdc, 100, 100 );
}
void DrawRect( HDC hdc )
{
	Rectangle( hdc,100, 100, 300, 300 );
	RoundRect( hdc, 300, 100, 600,300, 50, 50 );
}
void DrawEll( HDC hdc )
{
	Ellipse( hdc, 100, 100, 300, 300 );
	Ellipse( hdc, 300, 100, 600, 300 );
}
void DrawArc( HDC hdc ){
	Rectangle( hdc, 100, 100, 300, 300 );
	Arc( hdc, 100, 100, 300, 300, 200, 50, 50, 200 );
}
void DrawGrph( HDC hdc ){
	// �������ʺͻ�ˢ
	HPEN  hPenDash = CreatePen( PS_DASH, 1, RGB( 60, 70, 200 ));
	HPEN hPenSolid = CreatePen( PS_SOLID, 5, RGB( 128, 0, 128 ));
	HBRUSH hBrush = CreateSolidBrush( RGB( 200, 190, 230 ));
	// �����ʺͻ�ˢӦ�õ�DC��
	HGDIOBJ hOldPen = SelectObject( hdc, hPenDash );
	HGDIOBJ hOldBrush = SelectObject( hdc, hBrush );
	// ��ͼ
	Rectangle( hdc, 200, 100, 500, 300 );
	Ellipse( hdc, 200, 100, 500, 300 );
	MoveToEx( hdc, 350, 50, NULL );
	LineTo( hdc, 350, 200 );
	LineTo( hdc, 150, 200 );
	// ���ɵڶ�������
	SelectObject( hdc, hPenSolid);
	Arc( hdc, 200, 100, 500, 300, 350, 50, 150, 200 );
	// ��DC��ȡ����ͼ����
	SelectObject( hdc, hOldBrush );
	SelectObject( hdc, hOldPen );
	// �ͷŻ�ͼ����
	DeleteObject( hPenDash );
	DeleteObject( hPenSolid );
	DeleteObject( hBrush );
}
void OnPaint( HWND hWnd ){
	PAINTSTRUCT ps = {0};
	HDC hdc = BeginPaint( hWnd, &ps );

	// ����λͼ
	// 1. ���λͼ��Դ ( ����Ҫд���� )
	// 2. ����λͼ
	HBITMAP hBmp =  LoadBitmap( g_hInstance, ( LPCSTR )IDB_BITMAP2 );
	// 3. ����һ���͵�ǰDCƥ����ڴ�DC
	//  ͬʱ���ڴ��й���һ�����������ڴ�DC��Ӧ�����������
	/*
	   ����һ���ڴ�DC���ں˽ṹ��ͬʱ����һ���ڴ棬�ڴ�DCά������ڴ�
	   ������ڴ�ռ�Ĵ�С�͵�ǰDCά�����Դ��С��ͬ
	   ��ǰDCά�����Դ�ռ�Ĵ�С�ɴ��ڴ�С����
	*/
	HDC hMemDC = CreateCompatibleDC( hdc );
	// 4. ��λͼ�����ڴ�DC�У��ڴ�DC������λͼ��ͼ�������������л���
	/*  ��λͼ���ݴ����ڴ�DCά�����ǿ��ڴ��� */
	HGDIOBJ hOldBmp =  SelectObject( hMemDC, hBmp );
	// 5. ��ͼ ( ���� )
	/*
	   ���ڴ�DCά�����ǿ��ڴ��е����ݣ�
	   �Կ����ڴ�ķ�ʽһ���Է��뵱ǰDCά�����Դ���
	*/
	BITMAP bmpInfo = {0};
	GetObject( hBmp, sizeof(bmpInfo), &bmpInfo );

	BitBlt( hdc, 100, 100, bmpInfo.bmWidth, bmpInfo.bmHeight, hMemDC, 0, 0, SRCCOPY );

	StretchBlt( hdc, 100, 200, bmpInfo.bmWidth*2, bmpInfo.bmHeight*2, hMemDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, NOTSRCCOPY );

	// 6. ���ڴ�DC��ȡ��λͼ
	SelectObject( hMemDC, hOldBmp );
	// 7. �ͷ�λͼ
	DeleteObject( hBmp );
	// 8. �ͷ�DC
	DeleteDC( hMemDC );

//	DrawGrph( hdc );

/*
	// 1. ��������
	HPEN hPen = CreatePen( PS_DASH, 1, RGB( 240,0,0) );
	// 2. ������Ӧ�õ�DC��
	HGDIOBJ hOldPen =  SelectObject( hdc, hPen );

	// ������ˢ
//	HBRUSH hBrush = CreateSolidBrush( RGB( 200, 220, 220 ));
//	HBRUSH hBrush = CreateHatchBrush( HS_DIAGCROSS, RGB( 200, 220, 220 ));
	HGDIOBJ hBrush = GetStockObject( NULL_BRUSH );
	// ����ˢӦ�õ�DC��
	HGDIOBJ hOldBrush =  SelectObject( hdc, hBrush );
	// 3. ��ͼ
//	DrawLine( hdc );   // ����ֱ��
//	DrawRect( hdc );  // ���ƾ���
	DrawEll( hdc );      // ������Բ
//	DrawArc( hdc );
	// ��DC��ȡ����ˢ
	SelectObject( hdc, hOldBrush );
	// �ͷŻ�ˢ
//	DeleteObject( hBrush );

	// 4. ��DC��ȡ������
	SelectObject( hdc, hOldPen );
	// 5. �ͷŻ���
	DeleteObject( hPen );
*/

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
	wndCls.hbrBackground = CreateSolidBrush( RGB(220, 200, 220) );
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