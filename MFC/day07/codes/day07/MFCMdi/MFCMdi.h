
// MFCMdi.h : MFCMdi Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMFCMdiApp:
// �йش����ʵ�֣������ MFCMdi.cpp
//

class CMFCMdiApp : public CWinApp
{
public:
	CMFCMdiApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCMdiApp theApp;
