/*
#include <Windows.h>//win32 
#include <afx.h>//MFC
*/
#include <afxwin.h> // Win32+MFC
 
// 2 ������
class CMyFrameWnd:public CFrameWnd
{

};

// 1 Ӧ�ó���
class CMyWinApp:public CWinApp
{
public:
	// ��ʼ������
	virtual BOOL InitInstance();
	virtual int ExitInstance( );
	virtual int Run( );

};
int CMyWinApp::ExitInstance()
{
	AfxMessageBox("�û���Դ���ͷţ����ж��");
	return CWinApp::ExitInstance();
}
int CMyWinApp::Run()
{
	AfxMessageBox("������Ϣѭ��");
	return CWinApp::Run();
}

CMyWinApp theApp;//ȫ��Ӧ�ó������
BOOL CMyWinApp::InitInstance()
{
	// �û������̴Ӵ˿�ʼ��д�������Ĵ��ڳ���
	CMyFrameWnd* pFrame=new CMyFrameWnd;
	pFrame->Create(NULL,"MFCBase");
	m_pMainWnd = pFrame;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}
