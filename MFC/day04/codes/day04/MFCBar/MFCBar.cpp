#include <afxwin.h>
#include "resource.h"
#include <afxext.h>//��չ���ڵ�ͷ�ļ�

//����״ָ̬ʾ������
UINT gIndicators[]=
{
	0,
	IDS_TIME,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_OVR
};
// 1 ��ܴ�����
class CMyFrameWnd:public CFrameWnd
{
DECLARE_MESSAGE_MAP()
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer( UINT nIDEvent );
	afx_msg void OnMouseMove( UINT nFlags, CPoint point );
	afx_msg void OnNew();
	afx_msg void OnExit();
	afx_msg void OnTool();
	CToolBar m_wndToolbar;//����������
	CStatusBar m_wndStatus;//״̬������
};
BEGIN_MESSAGE_MAP(CMyFrameWnd,CFrameWnd)
	ON_WM_CREATE( )
	ON_COMMAND(ID_NEW,OnNew)
	ON_COMMAND(ID_EXIT,OnExit)
	ON_COMMAND(ID_TOOL,OnTool)
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE( )
END_MESSAGE_MAP( )
void CMyFrameWnd::OnMouseMove( UINT nFlags, CPoint point )
{
	// 1 ����ά�ĵ������ʽ��Ϊ�ַ�������
	CString strPt;
	strPt.Format("X=%d,Y=%d ����",point.x,point.y);
	// 2 ���ַ�����ʾ��λ�÷ŵ�״̬������ʽ
	m_wndStatus.SetPaneText(0,strPt);
}
void CMyFrameWnd::OnTimer( UINT nIDEvent )
{
	// 1 ��ȡ��ǰϵͳʱ��
	CTime t= CTime::GetCurrentTime();
	// 2 ��ʱ�����ת��Ϊ�ַ�������
	CString strTime = t.Format("%Y-%m-%d %H:%M:%S");
	// 3 ���ַ�����ʾ��ʱ��ŵ�״̬������ʽ
	m_wndStatus.SetPaneText(1,strTime);
}
void CMyFrameWnd::OnTool()
{
	if (m_wndToolbar.IsVisible())
	{
		ShowControlBar(&m_wndToolbar,FALSE,FALSE);
	}
	else
	{
		ShowControlBar(&m_wndToolbar,TRUE,FALSE);
	}
}
void CMyFrameWnd::OnNew()
{
	AfxMessageBox("OnNew");
}
void CMyFrameWnd::OnExit()
{
	PostQuitMessage(0);
}
int CMyFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// ������
	// 1 ��������������
	m_wndToolbar.Create(this,WS_VISIBLE|WS_CHILD|CBRS_GRIPPER|CBRS_TOOLTIPS|CBRS_FLYBY);
	// 2 ���ع�������Դ
	m_wndToolbar.LoadToolBar(IDR_TOOLBAR1);
	// 3 ͣ��������
	// 3.1 ���ù���������ͣ��
	m_wndToolbar.EnableDocking(CBRS_ALIGN_ANY );
	// 3.2 ���ÿ�ܴ�������ͣ��
	EnableDocking(CBRS_ALIGN_ANY );
	// 3.3 ͣ��������
	DockControlBar(&m_wndToolbar,AFX_IDW_DOCKBAR_TOP);

	// 4 ���ù��������ڱ���
	m_wndToolbar.SetWindowText("��׼������");

	// ״̬��
	// 1 ����״̬������
	m_wndStatus.Create(this);
	// 2 ����״̬��ָʾ��
	m_wndStatus.SetIndicators(gIndicators,sizeof(gIndicators)/sizeof(UINT));

	// ���ö�ʱ��
	SetTimer(1,1000,NULL);
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
	pFrame->LoadFrame(IDR_MENU1);
	m_pMainWnd=pFrame;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}