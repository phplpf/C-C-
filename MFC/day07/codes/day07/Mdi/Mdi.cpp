#include <afxwin.h>
#include <afxext.h>
#include "resource.h"

// 5 �ĵ���(֧�ֶ�̬����)
class CMyDoc:public CDocument
{
	DECLARE_DYNCREATE(CMyDoc)
public:
	CString m_strData;
};
IMPLEMENT_DYNCREATE(CMyDoc,CDocument)

// 4 ��ͼ��(֧�ֶ�̬����)
class CMyView:public CEditView
{
	DECLARE_DYNCREATE(CMyView)
	DECLARE_MESSAGE_MAP( )
protected:
	afx_msg void OnEnChange();
public:
	virtual void OnUpdate( CView* pSender, LPARAM lHint, CObject* pHint );
};
IMPLEMENT_DYNCREATE(CMyView,CEditView)
BEGIN_MESSAGE_MAP(CMyView,CEditView)
	ON_CONTROL_REFLECT(EN_CHANGE,OnEnChange)
END_MESSAGE_MAP( )
void CMyView::OnEnChange()
{
	// 1 ��ȡ����ĵ�
	CMyDoc* pDoc=(CMyDoc*)GetDocument();
	// 2 �����ͼ�����ݱ��浽�ĵ�
	GetWindowText(pDoc->m_strData);
	// 3 �ĵ�֪ͨ������ͼ���ݸ�����
	pDoc->UpdateAllViews(this);
}
void CMyView::OnUpdate( CView* pSender, LPARAM lHint, CObject* pHint )
{
	// 4 ��ȡ����ĵ�
	CMyDoc* pDoc=(CMyDoc*)GetDocument();
	// 5 ��ȡ�ĵ����ݷŵ���ͼ��������ʽ
	SetWindowText(pDoc->m_strData);

}
// 3 ���ĵ����ӿ�ܴ�����(֧�ֶ�̬����)
class CChildFrame:public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
DECLARE_MESSAGE_MAP()
protected:
	afx_msg void OnNewWnd();
};
IMPLEMENT_DYNCREATE(CChildFrame,CMDIChildWnd)
BEGIN_MESSAGE_MAP(CChildFrame,CMDIChildWnd)
	ON_COMMAND(ID_NEW_WND,OnNewWnd)
END_MESSAGE_MAP()
void CChildFrame::OnNewWnd()
{
	// 1 ��ȡ��ĵ�
	CDocument* pDoc=GetActiveDocument();
	// 2 �����ĵ���ȡ�ĵ�ģ��
	CDocTemplate* pTemplate=pDoc->GetDocTemplate();
	// 3 ʹ���ĵ�ģ�崴���µ��ӿ��
	CFrameWnd* pChildFrame= pTemplate->CreateNewFrame(pDoc,NULL);
	// 4 ��ʼ�������ӿ��
	pChildFrame->InitialUpdateFrame(pDoc,TRUE); 
}


// 1 ���ĵ�������ܴ�����
class CMainFrame:public CMDIFrameWnd
{

};
// 2 Ӧ�ó�����
class CMyWinApp:public CWinApp
{
public:
	virtual BOOL InitInstance();
	afx_msg void OnNew();
DECLARE_MESSAGE_MAP()
};
BEGIN_MESSAGE_MAP(CMyWinApp,CWinApp)
	ON_COMMAND(ID_NEW,OnNew)
END_MESSAGE_MAP()

CMyWinApp theApp;
void CMyWinApp::OnNew()
{
	OnFileNew();
}
BOOL CMyWinApp::InitInstance()
{
	CMainFrame* pFrame=new CMainFrame;
	pFrame->LoadFrame(IDR_MAIN);
	m_pMainWnd=pFrame;

	CMultiDocTemplate* pTemplate=new CMultiDocTemplate(
		IDR_CHILD,RUNTIME_CLASS(CMyDoc),
		RUNTIME_CLASS(CChildFrame),RUNTIME_CLASS(CMyView));
	AddDocTemplate(pTemplate);
	OnFileNew();
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}