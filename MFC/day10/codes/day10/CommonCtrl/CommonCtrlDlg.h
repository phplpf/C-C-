
// CommonCtrlDlg.h : 头文件
//

#pragma once


// CCommonCtrlDlg 对话框
class CCommonCtrlDlg : public CDialogEx
{
// 构造
public:
	CCommonCtrlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COMMONCTRL_DIALOG };

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
	CSpinButtonCtrl m_wndSpin;
	CProgressCtrl m_wndProgress;
	CSliderCtrl m_wndSlider;
	afx_msg void OnBnClickedMove();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
