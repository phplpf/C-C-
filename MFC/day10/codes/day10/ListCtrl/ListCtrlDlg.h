
// ListCtrlDlg.h : 头文件
//

#pragma once


// CListCtrlDlg 对话框
class CListCtrlDlg : public CDialogEx
{
// 构造
public:
	CListCtrlDlg(CWnd* pParent = NULL);	// 标准构造函数
	CImageList m_ilNormal;//图标列表
	CImageList m_ilSmall;//小图标列表
// 对话框数据
	enum { IDD = IDD_LISTCTRL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void InitListCtrl(void);
	CListCtrl m_wndList;
	void ShowData(CString strPath);
};
