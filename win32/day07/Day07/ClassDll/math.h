#pragma once   /* ��Ч��C�����е�ͷ�ļ���ʿ */  
#ifdef  CLASSDLL_EXPORT
#define EXT_CLASS _declspec(dllexport)   // dll
#else
#define EXT_CLASS _declspec(dllimport)  // exe
#endif
class  EXT_CLASS CMath{
public:
	int add( int m, int n );
	int sub( int m, int n );
};