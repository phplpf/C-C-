#include <afxwin.h>
#define WM_MY_MSG WM_USER+100
// 1 ��ܴ�����
class CMyFrameWnd:public CFrameWnd
{
	DECLARE_MESSAGE_MAP( )
public:
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnTest();
	afx_msg void OnTestRange(UINT nID);
	afx_msg void OnEnChange();
	afx_msg LRESULT OnMyMsg(WPARAM wParam,LPARAM lParam );
};
BEGIN_MESSAGE_MAP(CMyFrameWnd,CFrameWnd)
	// ������Ϣ
	ON_WM_CREATE()
	// ������Ϣ
	ON_COMMAND(1000,OnTest)
	ON_COMMAND_RANGE(1006,1008,OnTestRange)
	// ֪ͨ��Ϣ
	ON_EN_CHANGE(1010,OnEnChange)
	// �û��Զ�����Ϣ
	ON_MESSAGE(WM_MY_MSG,OnMyMsg)

END_MESSAGE_MAP( )
LRESULT CMyFrameWnd::OnMyMsg(WPARAM wParam,LPARAM lParam )
{
	CString strData;
	strData.Format("%d",wParam+lParam);
	AfxMessageBox(strData);
	return 0;
}
void CMyFrameWnd::OnEnChange()
{
	CWnd* pWnd=GetDlgItem(1010);
	CString strData;
	pWnd->GetWindowText(strData);
	AfxMessageBox(strData);
}
void CMyFrameWnd::OnTestRange(UINT nID)
{
	/*
	CString strInfo;
	strInfo.Format("nID:%d",nID);
	AfxMessageBox(strInfo);
	*/
	// ����Ϣ������ʾ��ť���ı�
}
void CMyFrameWnd::OnTest()
{
	//AfxMessageBox("CMyFrameWnd::OnTest");
	this->SendMessage(WM_MY_MSG,110,250);
}

int CMyFrameWnd::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	//AfxMessageBox("CMyFrameWnd::OnCreate");
	::CreateWindow("BUTTON","����",WS_CHILD|WS_VISIBLE,100,100,100,40,
		m_hWnd,(HMENU)1000,AfxGetInstanceHandle(),NULL);

	::CreateWindow("BUTTON","����6",WS_CHILD|WS_VISIBLE,100,200,100,40,
		m_hWnd,(HMENU)1006,AfxGetInstanceHandle(),NULL);
	::CreateWindow("BUTTON","����7",WS_CHILD|WS_VISIBLE,100,300,100,40,
		m_hWnd,(HMENU)1007,AfxGetInstanceHandle(),NULL);
	::CreateWindow("BUTTON","����8",WS_CHILD|WS_VISIBLE,100,400,100,40,
		m_hWnd,(HMENU)1008,AfxGetInstanceHandle(),NULL);

	::CreateWindow("EDIT","",WS_CHILD|WS_VISIBLE|WS_BORDER,300,100,200,40,
		m_hWnd,(HMENU)1010,AfxGetInstanceHandle(),NULL);
	return 0;
}

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
	pFrame->Create(NULL,"MFCMsg");
	m_pMainWnd=pFrame;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}