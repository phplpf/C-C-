
// UseAdoDlg.h : ͷ�ļ�
//

#pragma once

#include "AdoDatabase.h"
#include "AdoRecordset.h"
// CUseAdoDlg �Ի���
class CUseAdoDlg : public CDialogEx
{
// ����
public:
	CUseAdoDlg(CWnd* pParent = NULL);	// ��׼���캯��
	CAdoDatabase m_db;//���ݿ����Ӷ���
// �Ի�������
	enum { IDD = IDD_USEADO_DIALOG };

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
	afx_msg void OnBnClickedQuery();
	CListCtrl m_wndList;
	CComboBox m_wndClass;
	void InitClassCtrl(void);
	afx_msg void OnBnClickedAdd();
	CString m_strName;
	int m_nAge;
	CString m_strAddress;
	CString m_strClass;
	CString m_strId;//ѧԱID
	afx_msg void OnBnClickedDel();
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedModify();
	void InsertOrUpdate(BOOL IsInsert=TRUE);
};
