
// MdiView.cpp : CMdiView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Mdi.h"
#endif

#include "MdiDoc.h"
#include "MdiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMdiView

IMPLEMENT_DYNCREATE(CMdiView, CEditView)

BEGIN_MESSAGE_MAP(CMdiView, CEditView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMdiView ����/����

CMdiView::CMdiView()
{
	// TODO: �ڴ˴���ӹ������

}

CMdiView::~CMdiView()
{
}

BOOL CMdiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// ���û���

	return bPreCreated;
}


// CMdiView ��ӡ

BOOL CMdiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ׼��
	return CEditView::OnPreparePrinting(pInfo);
}

void CMdiView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ��ʼ��ӡ
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CMdiView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ������ӡ
	CEditView::OnEndPrinting(pDC, pInfo);
}


// CMdiView ���

#ifdef _DEBUG
void CMdiView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMdiView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMdiDoc* CMdiView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMdiDoc)));
	return (CMdiDoc*)m_pDocument;
}
#endif //_DEBUG


// CMdiView ��Ϣ�������
