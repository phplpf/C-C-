
// TreeCtrlDlg.h : ͷ�ļ�
//

#pragma once


// CTreeCtrlDlg �Ի���
class CTreeCtrlDlg : public CDialogEx
{
// ����
public:
	CTreeCtrlDlg(CWnd* pParent = NULL);	// ��׼���캯��
	CImageList m_ilNormal;
// �Ի�������
	enum { IDD = IDD_TREECTRL_DIALOG };

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
	CTreeCtrl m_wndTree;
	afx_msg void OnBnClickedButton1();
	CString m_strName;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
};
