
// ControlsDlg.h : ͷ�ļ�
//

#pragma once


// CControlsDlg �Ի���
class CControlsDlg : public CDialogEx
{
// ����
public:
	CControlsDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CONTROLS_DIALOG };

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
	int m_nEat;
	int m_nGame;
	int m_nSleep;
	afx_msg void OnBnClickedButton1();
	int m_nCity;
	int m_nMajor;
	CListBox m_wndList;
	afx_msg void OnBnClickedGet1();
	CString m_strIdol;
	CString m_strType;
	afx_msg void OnBnClickedGet2();
};
