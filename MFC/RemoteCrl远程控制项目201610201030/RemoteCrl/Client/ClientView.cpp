
// ClientView.cpp : CClientView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Client.h"
#endif

#include "ClientDoc.h"
#include "ClientView.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClientView

IMPLEMENT_DYNCREATE(CClientView, CView)

BEGIN_MESSAGE_MAP(CClientView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_MESSAGE(REFRESHSRC, ReFreshScr)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDBLCLK()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CClientView ����/����

CClientView::CClientView()
{
	// TODO: �ڴ˴���ӹ������
	ifstart=false;
	src=0;
	des=0;
}

CClientView::~CClientView()
{
	if(ifstart)
	{
	if(src)
		delete []src;
	if(des)
		delete []des;
	closesocket(s);
	WSACloseEvent(hEvent);
	closesocket(s1);
	WSACloseEvent(hEvent1);
	}
}

BOOL CClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CClientView ����

void CClientView::OnDraw(CDC* pDC)
{
	CClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if(!ifstart)
		return;	
	CRect rect;
	GetClientRect(&rect);
	//	pDC=GetDC();
	HDC hdc=pDC->GetSafeHdc();
	
	StretchDIBits(hdc,
		// destination rectangle
		0, 0, rect.Width(), rect.Height(),
		// source rectangle
		0, 0, screen.BmpCX, screen.BmpCY,
		src+screen.BmpInfoSize,
		(BITMAPINFO*)src,
		DIB_RGB_COLORS,
		SRCCOPY);
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CClientView ��ӡ

BOOL CClientView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CClientView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CClientView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CClientView ���

#ifdef _DEBUG
void CClientView::AssertValid() const
{
	CView::AssertValid();
}

void CClientView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CClientDoc* CClientView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClientDoc)));
	return (CClientDoc*)m_pDocument;
}
#endif //_DEBUG


// CClientView ��Ϣ�������


void CClientView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if(nChar==VK_ESCAPE)
	{
		if(ifstart)		//KillTimer(1);
			hThreadScreen->SuspendThread();
		CMainFrame *pMain=(CMainFrame*)AfxGetApp()->GetMainWnd();
		::SendMessage(pMain->GetSafeHwnd(),FULLSCREEN,0,0);

		if(ifstart)		//SetTimer(1,10,NULL);
			hThreadScreen->ResumeThread();
		return;
	}
	keymouse.style=PEER_KEY_DOWN;
	keymouse.nkey=nChar;
	PeerSendDataS(s,(char*)&keymouse,sizeof(keymouse),&retLen,
					  hEvent);
}


void CClientView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(!ifstart)
		return;
	keymouse.style=PEER_KEY_UP;
	keymouse.nkey=nChar;
	PeerSendDataS(s,(char*)&keymouse,sizeof(keymouse),&retLen,
					  hEvent);
}
LRESULT CClientView::ReFreshScr(WPARAM wp, LPARAM lp)
{	
	if(ifstart==0)
		screen.BmpSize=10000;
	else
		screen.BmpSize=0;

	if(!PeerSendDataS(s1,(char*)&screen,sizeof(screen),&retLen1,
					  hEvent1))
	{
		return -1;
	}
	if(!PeerRecvDataS(s1,(char*)&screen,sizeof(screen),&retLen1,
				  hEvent1))
	{
		return -1;
	}
	if(!PeerRecvDataS(s1,(char*)src,screen.BmpSize,&retLen1,
					  hEvent1))
	{
		return -1;
	}
/*	if(!(nTime++%10))
	{
		nTime = 0;
		CPoint point;
		GetCursorPos(&point);
		
		keymouse.style=PEER_CFM_OK;
		float fx,fy;
		CRect rect;
		GetClientRect(&rect);
		fx=(float)point.x/rect.Width();
		fy=(float)point.y/rect.Height();
		keymouse.x=65535*fx;
		keymouse.y=65535*fy;	
		if(!PeerSendDataS(s,(char*)&keymouse,sizeof(keymouse),&retLen, hEvent))
			return;		
	}*/
	Invalidate();
	return 0;
}

BOOL CClientView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(ifstart)
		return false;
	else
		return CView::OnEraseBkgnd(pDC);
}


void CClientView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if(!ifstart)
		return;
	keymouse.style=PEER_MOUSE_LDBCLICK;
	float fx,fy;
	CRect rect;
	GetClientRect(&rect);
	fx=(float)point.x/rect.Width();
	fy=(float)point.y/rect.Height();
	keymouse.x=65535*fx;
	keymouse.y=65535*fy;	
	PeerSendDataS(s,(char*)&keymouse,sizeof(keymouse),&retLen,
					  hEvent);
}


void CClientView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(!ifstart)
		return;
	keymouse.style=PEER_MOUSE_LEFTDOWN;
	float fx,fy;
	CRect rect;
	GetClientRect(&rect);
	fx=(float)point.x/rect.Width();
	fy=(float)point.y/rect.Height();
	keymouse.x=65535*fx;
	keymouse.y=65535*fy;	
	PeerSendDataS(s,(char*)&keymouse,sizeof(keymouse),&retLen,
					  hEvent);
}


void CClientView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if(!ifstart)
		return;
	keymouse.style=PEER_MOUSE_LEFTUP;
	float fx,fy;
	CRect rect;
	GetClientRect(&rect);
	fx=(float)point.x/rect.Width();
	fy=(float)point.y/rect.Height();
	keymouse.x=65535*fx;
	keymouse.y=65535*fy;	
	PeerSendDataS(s,(char*)&keymouse,sizeof(keymouse),&retLen,
					  hEvent);
}


void CClientView::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(!ifstart)
		return;
	keymouse.ctrl=PEER_MOUSE_MDBCLICK;
	float fx,fy;
	CRect rect;
	GetClientRect(&rect);
	fx=(float)point.x/rect.Width();
	fy=(float)point.y/rect.Height();
	keymouse.x=65535*fx;
	keymouse.y=65535*fy;	
	PeerSendDataS(s,(char*)&keymouse,sizeof(keymouse),&retLen,
					  hEvent);
}


void CClientView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if(!ifstart)
		return;
	keymouse.ctrl=PEER_MOUSE_MIDDLEDOWN;
	float fx,fy;
	CRect rect;
	GetClientRect(&rect);
	fx=(float)point.x/rect.Width();
	fy=(float)point.y/rect.Height();
	keymouse.x=65535*fx;
	keymouse.y=65535*fy;	
	PeerSendDataS(s,(char*)&keymouse,sizeof(keymouse),&retLen,
					  hEvent);
}


void CClientView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(!ifstart)
		return;
	keymouse.ctrl=PEER_MOUSE_MIDDLEUP;
	float fx,fy;
	CRect rect;
	GetClientRect(&rect);
	fx=(float)point.x/rect.Width();
	fy=(float)point.y/rect.Height();
	keymouse.x=65535*fx;
	keymouse.y=65535*fy;	
	PeerSendDataS(s,(char*)&keymouse,sizeof(keymouse),&retLen,
					  hEvent);
}


void CClientView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if(!ifstart)
		return;
	keymouse.style=PEER_MOUSE_RDBCLICK;
	float fx,fy;
	CRect rect;
	GetClientRect(&rect);
	fx=(float)point.x/rect.Width();
	fy=(float)point.y/rect.Height();
	keymouse.x=65535*fx;
	keymouse.y=65535*fy;	
	PeerSendDataS(s,(char*)&keymouse,sizeof(keymouse),&retLen,
					  hEvent);	
}


void CClientView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if(!ifstart)
		return;
	keymouse.style=PEER_MOUSE_RIGHTDOWN;
	float fx,fy;
	CRect rect;
	GetClientRect(&rect);
	fx=(float)point.x/rect.Width();
	fy=(float)point.y/rect.Height();
	keymouse.x=65535*fx;
	keymouse.y=65535*fy;	
	PeerSendDataS(s,(char*)&keymouse,sizeof(keymouse),&retLen,
					  hEvent);
}


void CClientView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(!ifstart)
		return;
	keymouse.style=PEER_MOUSE_RIGHTUP;
	float fx,fy;
	CRect rect;
	GetClientRect(&rect);
	fx=(float)point.x/rect.Width();
	fy=(float)point.y/rect.Height();
	keymouse.x=65535*fx;
	keymouse.y=65535*fy;	
	PeerSendDataS(s,(char*)&keymouse,sizeof(keymouse),&retLen,
					  hEvent);
}


void CClientView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(!ifstart)
		return;
	keymouse.style=PEER_MOUSE_MOVE;
	float fx,fy;
	CRect rect;
	GetClientRect(&rect);
	fx=(float)point.x/rect.Width();
	fy=(float)point.y/rect.Height();
	keymouse.x=65535*fx;
	keymouse.y=65535*fy;	
	PeerSendDataS(s,(char*)&keymouse,sizeof(keymouse),&retLen,
					  hEvent);
}
