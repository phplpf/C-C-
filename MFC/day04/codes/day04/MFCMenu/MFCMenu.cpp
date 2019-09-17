#include <afxwin.h>
#include "resource.h"

// 1 ��ܴ�����
class CMyFrameWnd:public CFrameWnd
{
	DECLARE_MESSAGE_MAP( )
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNew();
	afx_msg void OnExit();
	afx_msg void OnAbout();
	afx_msg void OnAboutUpdateCmdUI(CCmdUI*pCmdUI);
	afx_msg void OnContextMenu( CWnd* pWnd, CPoint pos );
	CMenu m_Menu;//�˵�����
};
BEGIN_MESSAGE_MAP(CMyFrameWnd,CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_NEW,OnNew)
	ON_COMMAND(ID_EXIT,OnExit)
	ON_COMMAND(ID_ABOUT,OnAbout)
	ON_UPDATE_COMMAND_UI(ID_ABOUT,OnAboutUpdateCmdUI)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP( )
void CMyFrameWnd::OnContextMenu( CWnd* pWnd, CPoint pos )
{
	// 1 ���ز˵���Դ
	CMenu menu;
	menu.LoadMenu(IDR_MENU2);
	// 2 ��ȡĳ���˵����µ��Ӳ˵�
	CMenu * pPopMenu = menu.GetSubMenu(1);
	// 3 ��ʾ�˵�
	pPopMenu->TrackPopupMenu(TPM_LEFTALIGN,pos.x,pos.y,this );

}
void CMyFrameWnd::OnAboutUpdateCmdUI(CCmdUI*pCmdUI)
{
	//pCmdUI->SetCheck(1);//���ò˵��ĸ�ѡ״̬
	//pCmdUI->SetRadio(TRUE);//���ò˵��ĵ�ѡ״̬
   pCmdUI->SetText("���������Ȩ");

}
void CMyFrameWnd::OnAbout()
{
	AfxMessageBox("CMyFrameWnd��ʵ�ֵ�OnAbout");
}
void CMyFrameWnd::OnExit()
{
	PostQuitMessage(0);
}
void CMyFrameWnd::OnNew()
{
	AfxMessageBox("CMyFrameWnd::OnNew");
}
int CMyFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// ��Ӳ˵�
	// 1 ���ز˵���Դ
	m_Menu.LoadMenu(IDR_MENU1);
	// 2 ���˵����õ�����
	SetMenu(&m_Menu);
	return 0;
}

// 2 Ӧ�ó�����
class CMyWinApp:public CWinApp
{
public:
	virtual BOOL InitInstance();
	afx_msg void OnAbout();
	DECLARE_MESSAGE_MAP()
};
BEGIN_MESSAGE_MAP(CMyWinApp,CWinApp)
	ON_COMMAND(ID_ABOUT,OnAbout)
END_MESSAGE_MAP()

CMyWinApp theApp;
void CMyWinApp::OnAbout()
{
	AfxMessageBox("CMyWinApp��ʵ�ֵĹ��ڶԻ���");
}
BOOL CMyWinApp::InitInstance()
{
	CMyFrameWnd* pFrame=new CMyFrameWnd;
	pFrame->Create(NULL,"MFCMenu");
	m_pMainWnd=pFrame;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}