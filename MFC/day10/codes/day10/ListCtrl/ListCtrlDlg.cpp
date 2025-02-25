
// ListCtrlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ListCtrl.h"
#include "ListCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CListCtrlDlg 对话框




CListCtrlDlg::CListCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CListCtrlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_wndList);
}

BEGIN_MESSAGE_MAP(CListCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CListCtrlDlg 消息处理程序

BOOL CListCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitListCtrl();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CListCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CListCtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CListCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CListCtrlDlg::InitListCtrl(void)
{
	// 1 创建图标列表
	m_ilNormal.Create(IDB_NORMAL,32,1,RGB(255,255,255));
	m_ilSmall.Create(IDB_SMALL,16,1,RGB(255,255,255));
	// 2 将图标列表设置到控件
	m_wndList.SetImageList(&m_ilNormal,LVSIL_NORMAL);
	m_wndList.SetImageList(&m_ilSmall,LVSIL_SMALL);
	// 3 添加控件的列(只在报表视图下显示)
	m_wndList.InsertColumn(0,"名称",LVCFMT_LEFT,120);
	m_wndList.InsertColumn(1,"大小",LVCFMT_LEFT,80);
	m_wndList.InsertColumn(2,"类型",LVCFMT_LEFT,80);
	m_wndList.InsertColumn(3,"修改日期",LVCFMT_LEFT,150);
	// 4 插入选项
	m_wndList.InsertItem(0,"软件安装包",0);
	m_wndList.SetItemText(0,2,"文件夹");
	m_wndList.InsertItem(1,"毕业设计.doc",1);
	m_wndList.InsertItem(2,"day01",0);
	m_wndList.InsertItem(3,"day01笔记.txt",1);
	m_wndList.SetItemText(3,1,"125 k");

	ShowData("c:");
}


void CListCtrlDlg::ShowData(CString strPath)
{
	//先清空列表控件
	m_wndList.DeleteAllItems();
	//使用CFileFind类，获取指定目录下的文件和子目录，放到列表控件中显式
	// InsertItem()、SetItemText()             （10 分钟）
	CFileFind find;
	BOOL bRet=find.FindFile(strPath+"/*.*");
	int nItem=0;
	while(bRet)
	{
		bRet = find.FindNextFile();
		CString strName = find.GetFileName();
		if (find.IsDirectory())
		{
			m_wndList.InsertItem(nItem,strName,0);
			//设置类型
			m_wndList.SetItemText(nItem,2,"文件夹");
		}
		else
		{
			m_wndList.InsertItem(nItem,strName,1);
			// 设置大小
			ULONGLONG nLen=find.GetLength();
			CString strLen;
			strLen.Format("%lld",nLen);
			m_wndList.SetItemText(nItem,1,strLen);
		}
		CTime t;
		// 最近修改时间
		find.GetLastWriteTime(t);
		CString strTime=t.Format("%Y-%m-%d %H:%M");
		m_wndList.SetItemText(nItem,3,strTime);
		nItem++;

	}
	find.Close();
    
}
