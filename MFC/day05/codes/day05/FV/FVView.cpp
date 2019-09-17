
// FVView.cpp : CFVView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "FV.h"
#endif

#include "FVDoc.h"
#include "FVView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFVView

IMPLEMENT_DYNCREATE(CFVView, CFormView)

BEGIN_MESSAGE_MAP(CFVView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CFVView ����/����

CFVView::CFVView()
	: CFormView(CFVView::IDD)
{
	// TODO: �ڴ˴���ӹ������

}

CFVView::~CFVView()
{
}

void CFVView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CFVView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CFVView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

}

void CFVView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFVView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CFVView ���

#ifdef _DEBUG
void CFVView::AssertValid() const
{
	CFormView::AssertValid();
}

void CFVView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CFVDoc* CFVView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFVDoc)));
	return (CFVDoc*)m_pDocument;
}
#endif //_DEBUG


// CFVView ��Ϣ�������
