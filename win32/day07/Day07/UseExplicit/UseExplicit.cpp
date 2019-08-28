#include <stdio.h>
#include <windows.h>
// 1. ���庯��ָ������
typedef int(*FUNC)( int m, int n );
int main( void )
{
	// 2. ���ض�̬��
	HMODULE hDll = LoadLibrary( "CppDll.dll" );
	printf("hDll: %d\n", hDll );
	// 3. ���ݺ��������ַ�������ȡ�����ľ��Ե�ַ
	FUNC myAdd = (FUNC)GetProcAddress( hDll, "CppDll_add");
	FUNC mySub = (FUNC)GetProcAddress( hDll, "CppDll_sub");
	FUNC myMul = (FUNC)GetProcAddress( hDll, "?CppDll_mul@@YAHHH@Z");
//	printf("myAdd: %p\n", myAdd );
	// 4. ���ݺ����ľ��Ե�ַ���ú���
	int sum = myAdd( 6, 1 );
	int sub = mySub( 6, 1 );
	int mul = myMul( 6, 1 );
	printf("sum = %d, sub=%d, mul=%d\n", sum, sub, mul );
	// 5. ж�ض�̬��
	FreeLibrary( hDll );
	getchar();
	return 0;
}