// ����lib�⣬�������������ĸ��ļ��и���CLib_add��CLib_sub��Դ��
#pragma comment(lib, "../Debug/CLib.lib")
int main(void)
{
	int sum = CLib_add( 10, 5 );
	int sub = CLib_sub( 10, 5 );
	printf( "sum=%d,sub=%d\n", sum, sub );
	getchar();
	return 0;
}