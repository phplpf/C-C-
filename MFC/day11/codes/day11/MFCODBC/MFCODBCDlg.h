
// MFCODBCDlg.h : ͷ�ļ�
//

#pragma once

#include <afxdb.h>

// CMFCODBCDlg �Ի���
class CMFCODBCDlg : public CDialogEx
{
// ����
public:
	CMFCODBCDlg(CWnd* pParent = NULL);	// ��׼���캯��
	CDatabase m_db;//���ݿ����Ӷ���
// �Ի�������
	enum { IDD = IDD_MFCODBC_DIALOG };

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
	afx_msg void OnClose();
	afx_msg void OnBnClickedQuery();
	CListCtrl m_wndList;
	void InitClassCtrl(void);
	CComboBox m_wndClass;
	afx_msg void OnBnClickedAdd();
	CString m_strName;
	int m_nAge;
	CString m_strAddress;
	CString m_strId;//ѧԱ���

	afx_msg void OnBnClickedDel();
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_strClass;
	afx_msg void OnBnClickedModify();
};
