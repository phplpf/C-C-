#include <stdio.h>
#include <windows.h>
HANDLE g_hEvent = 0; // �¼����
DWORD CALLBACK PrintProc( LPVOID pParam )
{
	while( 1 ){
		WaitForSingleObject( g_hEvent, INFINITE );
		ResetEvent( g_hEvent ); // ��λ
		printf("******************\n");
	}
	return 0;
}
DWORD CALLBACK CtrlProc( LPVOID pParam )
{
	while( 1 ){
		Sleep(1000); 
		SetEvent( g_hEvent );  // ����
	}
	return 0;
}
int main( void )
{
	// �����¼�
	g_hEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
	HANDLE hThreads[2];
	DWORD nID = 0;
	hThreads[0] = CreateThread( NULL, 0, PrintProc, NULL, 0, &nID );
	hThreads[1] = CreateThread( NULL, 0, CtrlProc, NULL, 0, &nID );
	getchar();
	// �رվ��
	CloseHandle( hThreads[0] );
	CloseHandle( hThreads[1] );
	CloseHandle( g_hEvent );
	return 0;
}