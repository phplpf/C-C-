
// MFCListBox.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCListBoxApp:
// �йش����ʵ�֣������ MFCListBox.cpp
//

class CMFCListBoxApp : public CWinApp
{
public:
	CMFCListBoxApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCListBoxApp theApp;