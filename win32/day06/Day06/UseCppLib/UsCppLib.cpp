// ����ͷ�ļ����������ʱ�Ҳ���printf��getchar������
#include <stdio.h>
// ���Ӻ����������������ʱ�Ҳ����Զ��庯��������
int CppLib_add( int, int );
int CppLib_sub( int, int );
// ���ӿ⺯����·�����������ʱ�޷���ȡԴ�������
#pragma comment(lib,"../Debug/CppLib.lib")
// C�⺯�������� ������C���Ժ��������д���
extern "C"int CLib_add( int, int );
extern "C"int CLib_sub( int, int );
// ����C�⺯����·��
#pragma comment(lib,"../Debug/CLib.lib")
int main(void)
{
	int sum = CppLib_add( 10, 5 );
	int sub = CppLib_sub( 10, 5 );
	printf("sum=%d, sub=%d\n", sum, sub );

	sum = CLib_add( 8, 3 );
	sub = CLib_sub( 8, 3 );
	printf("sum=%d, sub=%d\n", sum, sub );

	getchar();
	return 0;
}