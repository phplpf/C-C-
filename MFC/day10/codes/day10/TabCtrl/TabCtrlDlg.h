
// TabCtrlDlg.h : ͷ�ļ�
//

#pragma once

#include "Dlg1.h"
#include "Dlg2.h"

// CTabCtrlDlg �Ի���
class CTabCtrlDlg : public CDialogEx
{
// ����
public:
	CTabCtrlDlg(CWnd* pParent = NULL);	// ��׼���캯��
	CDlg1 m_dlg1;
	CDlg2 m_dlg2;
// �Ի�������
	enum { IDD = IDD_TABCTRL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_wndTab;
	void InitTabCtrl(void);
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
