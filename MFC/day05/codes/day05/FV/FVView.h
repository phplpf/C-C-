
// FVView.h : CFVView ��Ľӿ�
//

#pragma once

#include "resource.h"


class CFVView : public CFormView
{
protected: // �������л�����
	CFVView();
	DECLARE_DYNCREATE(CFVView)

public:
	enum{ IDD = IDD_FV_FORM };

// ����
public:
	CFVDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CFVView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // FVView.cpp �еĵ��԰汾
inline CFVDoc* CFVView::GetDocument() const
   { return reinterpret_cast<CFVDoc*>(m_pDocument); }
#endif

