
// ControlsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Controls.h"
#include "ControlsDlg.h"
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


// CControlsDlg �Ի���




CControlsDlg::CControlsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CControlsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nEat = 0;
	m_nGame = 0;
	m_nSleep = 0;
	m_nCity = 0;
	m_nMajor = 0;
	m_strIdol = _T("");
	m_strType = _T("");
}

void CControlsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_EAT, m_nEat);
	DDX_Check(pDX, IDC_GAME, m_nGame);
	DDX_Check(pDX, IDC_SLEEP, m_nSleep);
	DDX_Radio(pDX, IDC_RADIO1, m_nCity);
	DDX_Radio(pDX, IDC_RADIO4, m_nMajor);
	DDX_Control(pDX, IDC_LIST1, m_wndList);
	DDX_CBString(pDX, IDC_IDOl, m_strIdol);
	DDX_LBString(pDX, IDC_LIST1, m_strType);
}

BEGIN_MESSAGE_MAP(CControlsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CControlsDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_GET1, &CControlsDlg::OnBnClickedGet1)
	ON_BN_CLICKED(IDC_GET2, &CControlsDlg::OnBnClickedGet2)
END_MESSAGE_MAP()


// CControlsDlg ��Ϣ�������

BOOL CControlsDlg::OnInitDialog()
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
	m_nGame = 1;//��ѡ

	m_nMajor=2;//��ѡ
	m_nCity=0;//��ѡ

	UpdateData(FALSE);

	m_wndList.AddString("C/C++");
	m_wndList.AddString("Python");
	m_wndList.AddString("ϵͳ��ά");
	m_wndList.AddString("Java");
	m_wndList.AddString("UI");
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CControlsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CControlsDlg::OnPaint()
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
HCURSOR CControlsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CControlsDlg::OnBnClickedButton1()
{
	CString strHobby="���ã�";
	UpdateData(TRUE);
	if (m_nEat == 1)
	{
		strHobby+="�Է���";
	}
	if (m_nSleep == 1)
	{
		strHobby+="˯����";
	}
	if (m_nGame == 1)
	{
		strHobby+="����Ϸ��";
	}
	AfxMessageBox(strHobby);
	
	//��ѡ��ť������
	CString strCity="���ڳ��У�";
	switch(m_nCity){
	case 0:
		strCity+="����";
		break;
	case 1:
		strCity+="�Ϻ�";
		break;
	case 2:
		strCity+="����";
		break;
	}
	AfxMessageBox(strCity);
}


void CControlsDlg::OnBnClickedGet1()
{
	UpdateData(TRUE);
	AfxMessageBox(m_strIdol);
}
#include <vector>
void CControlsDlg::OnBnClickedGet2()
{
	/*
	UpdateData(TRUE);
	AfxMessageBox(m_strType);
	*/
	//std::vector<int > ints;
	CString strInfo;
	// ��ȡѡ���������
	int selCount=m_wndList.GetSelCount();
	int *pInt=new int[selCount];
	// ��ȡ���ѡ�������ֵ�����浽������
	
	m_wndList.GetSelItems(selCount,pInt);
	CString strText;
	for (int i=0;i<selCount;i++)
	{
		// ����ÿһ��ѡ�������ֵ����ȡѡ����ı�
		m_wndList.GetText( pInt[i],strText);
		strInfo+=strText;
	}
	delete[] pInt;
	AfxMessageBox(strInfo);
	
	
}
