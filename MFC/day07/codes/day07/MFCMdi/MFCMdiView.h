
// MFCMdiView.h : CMFCMdiView ��Ľӿ�
//

#pragma once


class CMFCMdiView : public CEditView
{
protected: // �������л�����
	CMFCMdiView();
	DECLARE_DYNCREATE(CMFCMdiView)

// ����
public:
	CMFCMdiDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMFCMdiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MFCMdiView.cpp �еĵ��԰汾
inline CMFCMdiDoc* CMFCMdiView::GetDocument() const
   { return reinterpret_cast<CMFCMdiDoc*>(m_pDocument); }
#endif

