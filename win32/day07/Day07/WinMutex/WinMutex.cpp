#include <windows.h>
#include <stdio.h>
HANDLE g_hMutex = 0;  // ������
// �̴߳�����
DWORD CALLBACK TestProc( LPVOID pParam ){
	char* pszText = (char*)pParam;
	while( 1 ){
		// �Ⱥ򻥳������ź�
		WaitForSingleObject( g_hMutex, INFINITE );
		for( int i=0 ;i<strlen(pszText); i++){
			printf( "%c", pszText[i] );
			Sleep(10);
		}
		printf("\n");
		// �ͷŻ�����
		ReleaseMutex( g_hMutex );
		Sleep(10);
	}
	return 0;
}
DWORD CALLBACK TestProc2( LPVOID pParam ){
	char* pszTest  = (char*)pParam;
	while( 1 ){
		WaitForSingleObject( g_hMutex, INFINITE );
		for( int i=0; i<strlen(pszTest); i++ ){
			printf("%c", pszTest[i]);
			Sleep(10);
		}
		printf("\n");
		ReleaseMutex( g_hMutex );
		Sleep(10);
	}
	return 0;
}
int main( void ){
	// ��������
	g_hMutex = CreateMutex( NULL, FALSE, "Mutex");
	DWORD nID = 0;
	char* pszText = "********";
	// �����߳�
	HANDLE hThread = CreateThread( NULL, 0, TestProc, pszText, 0, &nID );
	char* pszText2 = "--------";
	HANDLE hThread2 = CreateThread( NULL, 0, TestProc2, pszText2, 0,&nID );
	getchar();
	// �ر��߳̾��
	CloseHandle( hThread );
	CloseHandle( hThread2 );
	// �رջ�����
	CloseHandle( g_hMutex );
	return 0;
}