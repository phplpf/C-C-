
// CommonCtrlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommonCtrl.h"
#include "CommonCtrlDlg.h"
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


// CCommonCtrlDlg �Ի���




CCommonCtrlDlg::CCommonCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCommonCtrlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCommonCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPIN1, m_wndSpin);
	DDX_Control(pDX, IDC_PROGRESS1, m_wndProgress);
	DDX_Control(pDX, IDC_SLIDER1, m_wndSlider);
}

BEGIN_MESSAGE_MAP(CCommonCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MOVE, &CCommonCtrlDlg::OnBnClickedMove)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CCommonCtrlDlg ��Ϣ�������

BOOL CCommonCtrlDlg::OnInitDialog()
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
	// 1 ���÷�Χ
	m_wndSpin.SetRange(0,1000);
	m_wndProgress.SetRange(0,1000);
	m_wndSlider.SetRange(0,1000);
	// 2 ��������
	UDACCEL accel[2]={0};
	accel[0].nSec =1;
	accel[0].nInc  =5;
	accel[1].nSec =2;
	accel[1].nInc  =100;
	m_wndSpin.SetAccel(2,accel);
	// ���ò���
	m_wndProgress.SetStep(100);
	// ���ÿ̶�
	m_wndSlider.SetTicFreq(100);
	m_wndSlider.SetPageSize(200);
	m_wndSlider.SetLineSize(100);
	// 3 ���õ�ǰֵ(λ��)
	m_wndSpin.SetPos(100);
	m_wndProgress.SetPos(m_wndSpin.GetPos());
	m_wndSlider.SetPos(m_wndSpin.GetPos());

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCommonCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCommonCtrlDlg::OnPaint()
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
HCURSOR CCommonCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCommonCtrlDlg::OnBnClickedMove()
{
	// 1 ������ǰ��һ������
	m_wndProgress.StepIt();
	// 2 ��ȡ��������λ��
	int nPos = m_wndProgress.GetPos();
	// 3 ���õ����������ؼ�
	m_wndSlider.SetPos(nPos);
	m_wndSpin.SetPos(nPos);

}


void CCommonCtrlDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if((CSpinButtonCtrl*)pScrollBar == &m_wndSpin)
	{
		int nPos = m_wndSpin.GetPos();
		m_wndSlider.SetPos(nPos);
		m_wndProgress.SetPos(nPos);

	}
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CCommonCtrlDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
