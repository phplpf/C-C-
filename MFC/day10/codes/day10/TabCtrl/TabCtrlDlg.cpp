
// TabCtrlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TabCtrl.h"
#include "TabCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTabCtrlDlg �Ի���




CTabCtrlDlg::CTabCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTabCtrlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTabCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_wndTab);
}

BEGIN_MESSAGE_MAP(CTabCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CTabCtrlDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CTabCtrlDlg ��Ϣ�������

BOOL CTabCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitTabCtrl();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTabCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTabCtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTabCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTabCtrlDlg::InitTabCtrl(void)
{
	// 1 ��ӱ�ǩ
	m_wndTab.InsertItem(0,"��ɫ��ǩ");
	m_wndTab.InsertItem(1,"����ǩ");
	// 2 ������ǩ��Ӧ���ӶԻ���
	m_dlg1.Create(IDD_DIALOG1,&m_wndTab);
	m_dlg2.Create(IDD_DIALOG2,&m_wndTab);

	// 3 ����TabCtrl�Ĵ�С�������Ի����С
	CRect rt;
	m_wndTab.GetClientRect(&rt);
	rt.top+=20;
	rt.left+=1;
	rt.bottom-=1;
	rt.right-=1;
	m_dlg1.MoveWindow(&rt);
	m_dlg2.MoveWindow(&rt);
	// 4 ��ʾ�Ի���
	m_dlg1.ShowWindow(SW_SHOW);
	m_dlg2.ShowWindow(SW_HIDE);
}


void CTabCtrlDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 1 ��ȡ��ǰѡ���Ҫ���õĺ���ʱ GetCurSel()  (10����)
	// ���ݵ�ǰѡ����öԻ������ʽ״̬
	int nSel=m_wndTab.GetCurSel();
	switch (nSel)
	{
	case 0:
		m_dlg1.ShowWindow(SW_SHOW);
		m_dlg2.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_dlg2.ShowWindow(SW_SHOW);
		m_dlg1.ShowWindow(SW_HIDE);
		break;
	}
	*pResult = 0;
}
