#include <windows.h>
#include <stdio.h>
// �̴߳�����
DWORD CALLBACK TestProc( LPVOID pParam ){
	char* pszText = (char*)pParam;
	while( 1 ){
		for( int i=0 ;i<strlen(pszText); i++){
			printf( "%c", pszText[i] );
			Sleep(10);
		}
		printf("\n");
	}
	return 0;
}
DWORD CALLBACK TestProc2( LPVOID pParam ){
	char* pszTest  = (char*)pParam;
	while( 1 ){
		for( int i=0; i<strlen(pszTest); i++ ){
			printf("%c", pszTest[i]);
			Sleep(10);
		}
		printf("\n");
	}
	return 0;
}
int main( void ){
	DWORD nID = 0;
	char* pszText = "********";
	// �����߳�
	HANDLE hThread = CreateThread( NULL, 0, TestProc, pszText, 0, &nID );
	char* pszText2 = "--------";
	HANDLE hThread2 = CreateThread( NULL, 0, TestProc2, pszText2, 0,&nID );
	getchar();
//	ResumeThread( hThread2 );  // �߳�����ִ��
//	SuspendThread( hThread );   // �̹߳���
//	getchar();
	// �ر��߳̾��
	CloseHandle( hThread );
	CloseHandle( hThread2 );

/*	nID = GetCurrentThreadId();
	HANDLE hThread = GetCurrentThread();
	printf("�߳�ID�� %d, �߳̾��: %d\n", nID, hThread);
	hThread = OpenThread( THREAD_ALL_ACCESS, TRUE, nID );
	printf(" �߳̾��: %d\n", hThread);
	CloseHandle(hThread);*/
	getchar();
	return 0;
}