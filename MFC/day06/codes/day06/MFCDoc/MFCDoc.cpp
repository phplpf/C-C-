#include <afxwin.h>
#include "resource.h"
#include <afxext.h>//CEditView

class CMyClass:public CCmdTarget
{
	DECLARE_MESSAGE_MAP()
protected:
	afx_msg void OnTest();
};
BEGIN_MESSAGE_MAP(CMyClass,CCmdTarget)
	ON_COMMAND(ID_TEST,OnTest)
END_MESSAGE_MAP( )
void CMyClass::OnTest()
{
	AfxMessageBox("CMyClass::OnTest");
}


// 4 �ĵ���
class CMyDoc:public CDocument
{
public:
	CMyDoc()
	{
		m_strData="Hello World";
	}
	afx_msg void OnTest();
	virtual BOOL OnCmdMsg( UINT nID, int nCode, void* pExtra, 
		AFX_CMDHANDLERINFO* pHandlerInfo );
	CString m_strData;
	CMyClass m_myObject;
DECLARE_MESSAGE_MAP( )
};
BEGIN_MESSAGE_MAP(CMyDoc,CDocument)
	ON_COMMAND(ID_TEST,OnTest)
END_MESSAGE_MAP()
BOOL CMyDoc::OnCmdMsg( UINT nID, int nCode, void* pExtra,
	AFX_CMDHANDLERINFO* pHandlerInfo )
{
	if (m_myObject.OnCmdMsg(nID,nCode,pExtra,pHandlerInfo))
		return TRUE;
	return CDocument::OnCmdMsg(nID,nCode,pExtra,pHandlerInfo);
}

void CMyDoc::OnTest()
{
	AfxMessageBox("CMyDoc::OnTest");
}

// 3 ��ͼ��(֧�ֶ�̬����)
class CMyView:public CEditView
{
	DECLARE_DYNCREATE(CMyView)
public:
	virtual void OnInitialUpdate( );
};
IMPLEMENT_DYNCREATE(CMyView,CEditView)
void CMyView::OnInitialUpdate()
{
	// 1 ��ȡ����ͼ�������ĵ�
	 CMyDoc * pDoc=(CMyDoc*)GetDocument();
	// 2 ���ĵ����ݷŵ���ͼ��������ʾ
	 SetWindowText(pDoc->m_strData);
}
// 1 ��ܴ�����
class CMyFrameWnd:public CFrameWnd
{

};
// 2 Ӧ�ó�����
class CMyWinApp:public CWinApp
{
public:
	virtual BOOL InitInstance();
};
CMyWinApp theApp;
BOOL CMyWinApp::InitInstance()
{
	CMyFrameWnd* pFrame=new CMyFrameWnd;
	CCreateContext cxt;
	cxt.m_pNewViewClass = RUNTIME_CLASS(CMyView);
	cxt.m_pCurrentDoc = new CMyDoc;
	pFrame->LoadFrame(IDR_MENU1,WS_OVERLAPPEDWINDOW,NULL,&cxt);
	pFrame->InitialUpdateFrame(NULL,TRUE);
	m_pMainWnd=pFrame;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}
 