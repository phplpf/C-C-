
// MFCDrawView.h : CMFCDrawView ��Ľӿ�
//

#pragma once


class CMFCDrawView : public CView
{
protected: // �������л�����
	CMFCDrawView();
	DECLARE_DYNCREATE(CMFCDrawView)

// ����
public:
	CMFCDrawDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMFCDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDc();
	afx_msg void OnDcClient();
	afx_msg void OnPaint();
	afx_msg void OnGdiPen();
	afx_msg void OnGdiBrush();
	afx_msg void OnGdiFont();
	afx_msg void OnGdiBmp();
	afx_msg void OnGdiRgn();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // MFCDrawView.cpp �еĵ��԰汾
inline CMFCDrawDoc* CMFCDrawView::GetDocument() const
   { return reinterpret_cast<CMFCDrawDoc*>(m_pDocument); }
#endif

