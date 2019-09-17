
// MFCDrawView.cpp : CMFCDrawView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MFCDraw.h"
#endif

#include "MFCDrawDoc.h"
#include "MFCDrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCDrawView

IMPLEMENT_DYNCREATE(CMFCDrawView, CView)

BEGIN_MESSAGE_MAP(CMFCDrawView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DC, &CMFCDrawView::OnDc)
	ON_COMMAND(ID_DC_CLIENT, &CMFCDrawView::OnDcClient)
	ON_WM_PAINT()
	ON_COMMAND(ID_GDI_PEN, &CMFCDrawView::OnGdiPen)
	ON_COMMAND(ID_GDI_BRUSH, &CMFCDrawView::OnGdiBrush)
	ON_COMMAND(ID_GDI_FONT, &CMFCDrawView::OnGdiFont)
	ON_COMMAND(ID_GDI_BMP, &CMFCDrawView::OnGdiBmp)
	ON_COMMAND(ID_GDI_RGN, &CMFCDrawView::OnGdiRgn)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CMFCDrawView ����/����

CMFCDrawView::CMFCDrawView()
{
	// TODO: �ڴ˴���ӹ������

}

CMFCDrawView::~CMFCDrawView()
{
}

BOOL CMFCDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMFCDrawView ����

void CMFCDrawView::OnDraw(CDC* /*pDC*/)
{
	CMFCDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMFCDrawView ��ӡ

BOOL CMFCDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMFCDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMFCDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMFCDrawView ���

#ifdef _DEBUG
void CMFCDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDrawDoc* CMFCDrawView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDrawDoc)));
	return (CMFCDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCDrawView ��Ϣ�������


void CMFCDrawView::OnDc()
{
	// CDC���ʹ��
	// 1 ����DC
	CDC dc;
	dc.CreateDC("DISPLAY",NULL,NULL,NULL);
	// 2 ʹ��DC������
	dc.TextOut(0,0,"Hello CDC");
	// 3 ɾ��DC
	dc.DeleteDC();
}


void CMFCDrawView::OnDcClient()
{
	// CClientDC��ʹ��
	CClientDC dc(this);
	dc.TextOut(0,0,"Hello CClientDC");

}


void CMFCDrawView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.TextOut(0,100,"Hello CPaintDC");
	//OnGdiBmp();
}


void CMFCDrawView::OnGdiPen()
{
	// ����
	CPen pen(PS_DASHDOT ,0,RGB(255,0,0));
	CClientDC dc(this);
	CPen *pOldPen = dc.SelectObject(&pen);
	dc.Rectangle(100,100,300,300);
	dc.SelectObject(pOldPen);
	pen.DeleteObject();

}


void CMFCDrawView::OnGdiBrush()
{
	// ��ˢ (��ɫ����Ӱ��λͼ)
	//CBrush brush(HS_CROSS ,RGB(0,0,255));
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP1);
    CBrush brush(&bmp);
	CClientDC dc(this);
	CBrush* pOldBrush= dc.SelectObject(&brush);
	dc.Rectangle(100,100,500,500);
	dc.SelectObject(pOldBrush);
	brush.DeleteObject();
}
void CMFCDrawView::OnGdiFont()
{
	// ����(CFont font;font.CreatePointFont(,""))
	CFont font;
	font.CreatePointFont(1000,"����");
	CClientDC dc(this);
	CFont* pOldFoint = dc.SelectObject(&font);
	dc.TextOut(100,100,"Hello CFont");
	dc.SelectObject(pOldFoint);
	font.DeleteObject();
}


void CMFCDrawView::OnGdiBmp()
{
	// λͼ
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP2);
	CClientDC dc(this);
	CDC dcBmp;
	dcBmp.CreateCompatibleDC(&dc);
	dcBmp.SelectObject(&bmp);
	//dc.BitBlt(0,0,216,144,&dcBmp,0,0,SRCCOPY);
	CRect rt;
	GetClientRect(&rt);
	dc.StretchBlt(0,0,rt.Width(),rt.Height(),&dcBmp,0,0,216,144,SRCCOPY);
	dcBmp.DeleteDC();
	bmp.DeleteObject();
}


void CMFCDrawView::OnGdiRgn()
{
	// ����(��������)
	// 1 ��������
	CRgn rgn1,rgn2;
	rgn1.CreateEllipticRgn(100,100,300,300);
	rgn2.CreateEllipticRgn(200,100,400,300);
	// 2 ��������
	rgn1.CombineRgn(&rgn1,&rgn2,RGN_AND);
	// 3 �������
	CClientDC dc(this);
	CBrush brush(RGB(0,0,255));
	dc.FillRgn(&rgn1,&brush);
}


BOOL CMFCDrawView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//return FALSE;
	return CView::OnEraseBkgnd(pDC);
}
