
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

#include "TrueColorToolBar.h"

#define FULLSCREEN WM_USER+10011
class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:
	BOOL	m_start;
	WINDOWPLACEMENT m_OldWndPlacement;	//��������ԭ����λ�� 
	BOOL m_bFullScreen;					//ȫ����ʾ��־ 
	CRect m_FullScreenRect;				//��ʾȫ����ʾʱ�Ĵ���λ�� 
// ����
public:
	void FullScreenShow(BOOL flag);
	static UINT OnRrefreshScreen(LPVOID lparam) ;//�̴߳�����
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CStatusBar        m_wndStatusBar;
	CTrueColorToolBar    m_wndToolBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnToolStart();
	afx_msg void OnToolFullscreen();
	afx_msg void OnToolDisconnect();
	afx_msg void OnToolExit();
	afx_msg LRESULT OnFullScreen(WPARAM wp,LPARAM lp);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};


