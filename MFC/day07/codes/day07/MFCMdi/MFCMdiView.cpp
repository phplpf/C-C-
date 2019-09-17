
// MFCMdiView.cpp : CMFCMdiView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MFCMdi.h"
#endif

#include "MFCMdiDoc.h"
#include "MFCMdiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCMdiView

IMPLEMENT_DYNCREATE(CMFCMdiView, CEditView)

BEGIN_MESSAGE_MAP(CMFCMdiView, CEditView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCMdiView ����/����

CMFCMdiView::CMFCMdiView()
{
	// TODO: �ڴ˴���ӹ������

}

CMFCMdiView::~CMFCMdiView()
{
}

BOOL CMFCMdiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// ���û���

	return bPreCreated;
}


// CMFCMdiView ��ӡ

BOOL CMFCMdiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ׼��
	return CEditView::OnPreparePrinting(pInfo);
}

void CMFCMdiView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ��ʼ��ӡ
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CMFCMdiView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ������ӡ
	CEditView::OnEndPrinting(pDC, pInfo);
}


// CMFCMdiView ���

#ifdef _DEBUG
void CMFCMdiView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMFCMdiView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMFCMdiDoc* CMFCMdiView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCMdiDoc)));
	return (CMFCMdiDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCMdiView ��Ϣ�������
