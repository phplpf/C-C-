
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "Client.h"

#include "MainFrm.h"
#include "ClientView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_TOOL_START, &CMainFrame::OnToolStart)
	ON_COMMAND(ID_TOOL_FULLSCREEN, &CMainFrame::OnToolFullscreen)
	ON_COMMAND(ID_TOOL_DISCONNECT, &CMainFrame::OnToolDisconnect)
	ON_COMMAND(ID_TOOL_EXIT, &CMainFrame::OnToolExit)
	ON_MESSAGE(FULLSCREEN,OnFullScreen)
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	m_bFullScreen = FALSE;
	m_start = false;
	GetPrivateProfileString("Network", "REMOTEIP", "127.0.0.1", ADDRESS, 16, ".\\Client.ini");
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	SetMenu(NULL);
	m_wndToolBar.SetButtonText(m_wndToolBar.CommandToIndex(ID_TOOL_START),	"�� ��");	//
	m_wndToolBar.SetButtonText(m_wndToolBar.CommandToIndex(ID_TOOL_FULLSCREEN),		"ȫ ��");
	m_wndToolBar.SetButtonText(m_wndToolBar.CommandToIndex(ID_TOOL_DISCONNECT),		"�� ��");
	m_wndToolBar.SetButtonText(m_wndToolBar.CommandToIndex(ID_TOOL_EXIT),		"�� ��");
	CRect rectToolBar;	
	// set up toolbar button sizes
	m_wndToolBar.LoadTrueColorToolBar(32, IDB_TOOL_HOT, IDB_TOOL_NOR, IDB_TOOL_DIS);

	m_wndToolBar.GetItemRect(0, &rectToolBar);
	m_wndToolBar.SetSizes(rectToolBar.Size(), CSize(32,32));

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������


void CMainFrame::OnToolStart()
{
	// TODO: �ڴ���������������
	m_start=!m_start;
	CClientView* sctrl=(CClientView*)GetActiveView();
  	sctrl->SetFocus();
	sctrl->ifstart=m_start;
	//
	if(m_start)
	{		
		if(!(sctrl->src=new char[3*1024*1024]))
			return;
     		if(!(sctrl->des=new char[3*1024*1024]))
			return;
		sctrl->hEvent=WSACreateEvent();
		if(sctrl->hEvent==WSA_INVALID_EVENT)
		{
			return;
		}
		if(!PeerCreateSocket(&sctrl->s,PEER_STREAM))
		{
			WSACloseEvent(sctrl->hEvent);
			return;
		}
		if(!PeerConnectSocket(sctrl->s,ADDRESS,8111))
		{
			WSACloseEvent(sctrl->hEvent);
			closesocket(sctrl->s);
			return;
		}
		sctrl->com.CommandID=PEER_KEYMOUSE;
		if(!PeerSendDataS(sctrl->s,(char*)&sctrl->com,sizeof(sctrl->com),&sctrl->retLen,sctrl->hEvent))
		{
			WSACloseEvent(sctrl->hEvent);
			closesocket(sctrl->s);
			return;
		}



		Sleep(100);
		sctrl->hEvent1=WSACreateEvent();
		if(sctrl->hEvent1==WSA_INVALID_EVENT)
		{
			return;
		}
		if(!PeerCreateSocket(&sctrl->s1,PEER_STREAM))
		{
			WSACloseEvent(sctrl->hEvent1);
			return;
		}
		if(!PeerConnectSocket(sctrl->s1,ADDRESS,8111))
		{
			WSACloseEvent(sctrl->hEvent1);
			closesocket(sctrl->s1);
			return;
		}	
		sctrl->com1.CommandID=PEER_SCREEN_GET;
		if(!PeerSendDataS(sctrl->s1,(char*)&sctrl->com1,sizeof(sctrl->com1),&sctrl->retLen1,sctrl->hEvent1))
		{
			WSACloseEvent(sctrl->hEvent1);
			closesocket(sctrl->s1);
			return;
		}
		//sctrl->SetTimer( 1,100,NULL);
		g_ExitThread = FALSE;
		hThreadScreen = AfxBeginThread(OnRrefreshScreen, sctrl);
		m_wndStatusBar.SetPaneText(0, "Զ����Ļ������ʼ!");
	}
	else
	{
		DWORD dwExitCode;
		g_ExitThread = TRUE;
		GetExitCodeThread(hThreadScreen, &dwExitCode);
		TerminateThread(hThreadScreen, dwExitCode);
		//sctrl->KillTimer(1);
		if(sctrl->src)
			delete []sctrl->src;
		if(sctrl->des)
			delete []sctrl->des;
		sctrl->src=0;
		sctrl->des=0;
		closesocket(sctrl->s);
		WSACloseEvent(sctrl->hEvent);
		closesocket(sctrl->s1);
		WSACloseEvent(sctrl->hEvent1);
		m_wndStatusBar.SetPaneText(0, "Զ����Ļ��������!");
	}
}


void CMainFrame::OnToolFullscreen()
{
	// TODO: �ڴ���������������
	FullScreenShow(TRUE);
}
void CMainFrame::FullScreenShow(BOOL flag)
{	
	CRect mainRect;
	if(flag)
	{
		GetWindowPlacement(&m_OldWndPlacement); 
		CRect WindowRect;
		GetWindowRect(&WindowRect);
		CRect ClientRect;
		RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &ClientRect); 
		ClientToScreen(&ClientRect); 
		//��ȡ��Ļ�ķֱ��� 
		int nFullWidth=GetSystemMetrics(SM_CXSCREEN); 
		int nFullHeight=GetSystemMetrics(SM_CYSCREEN); 
		// ������������Ŀͻ���ȫ����ʾ����(0,0)��(nFullWidth, nFullHeight)����, ��(0,0)��(nFullWidth, nFullHeight)������������ԭ���ںͳ�������֮��� �ͻ���λ�ü�Ĳ�ֵ, �͵õ�ȫ����ʾ�Ĵ���λ�� 
		m_FullScreenRect.left=WindowRect.left - ClientRect.left; 
		m_FullScreenRect.top=WindowRect.top - ClientRect.top; 
		m_FullScreenRect.right=WindowRect.right - ClientRect.right + nFullWidth; 
		m_FullScreenRect.bottom=WindowRect.bottom - ClientRect.bottom + nFullHeight; 
		m_bFullScreen=TRUE; // ����ȫ����ʾ��־Ϊ TRUE 
		// ����ȫ����ʾ״̬ 
		WINDOWPLACEMENT wndpl; 
		wndpl.length=sizeof(WINDOWPLACEMENT); 
		wndpl.flags=0; 
		wndpl.showCmd=SW_SHOWNORMAL; 
		wndpl.rcNormalPosition=m_FullScreenRect; 
		SetWindowPlacement(&wndpl);
	}
	else
	{		
		if(m_bFullScreen) 
		{
			//�˳�ȫ����ʾ, �ָ�ԭ������ʾ 
			m_wndStatusBar.ShowWindow(SW_SHOWNORMAL);
			m_wndToolBar.ShowWindow(SW_SHOWNORMAL);
			ShowWindow(SW_SHOWNORMAL); 
			SetWindowPlacement(&m_OldWndPlacement);
		
		}
	}	
}

void CMainFrame::OnToolDisconnect()
{
	// TODO: �ڴ���������������
	CClientView* sctrl=(CClientView*)GetActiveView();

	PeerShutDownSocket(sctrl->s);
	PeerShutDownSocket(sctrl->s1);

	PeerCloseSocket(sctrl->s);
	PeerCloseSocket(sctrl->s1);
}


void CMainFrame::OnToolExit()
{
	// TODO: �ڴ���������������
	SendMessage(WM_CLOSE);
}

LRESULT CMainFrame::OnFullScreen(WPARAM wp,LPARAM lp)
{
	FullScreenShow(FALSE);
	return 0;
}
UINT CMainFrame::OnRrefreshScreen(LPVOID lparam) 
{
	CClientView* pWnd = (CClientView*)lparam;
	while(!g_ExitThread)
	{
		pWnd->SendMessage(REFRESHSRC, 0, 0);
		Sleep(10);
	}
	return 0;
}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if(m_bFullScreen) 
	{
		lpMMI->ptMaxSize.x=m_FullScreenRect.Width(); 
		lpMMI->ptMaxSize.y=m_FullScreenRect.Height(); 
		lpMMI->ptMaxPosition.x=m_FullScreenRect.Width(); 
		lpMMI->ptMaxPosition.y=m_FullScreenRect.Height(); 
		// ����Track�ߴ�ҲҪ�ı� 
		lpMMI->ptMaxTrackSize.x=m_FullScreenRect.Width(); 
		lpMMI->ptMaxTrackSize.y=m_FullScreenRect.Height(); 
	}	
}
