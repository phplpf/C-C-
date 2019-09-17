
// ListCtrlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ListCtrl.h"
#include "ListCtrlDlg.h"
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


// CListCtrlDlg �Ի���




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


// CListCtrlDlg ��Ϣ�������

BOOL CListCtrlDlg::OnInitDialog()
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
	InitListCtrl();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CListCtrlDlg::OnPaint()
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
HCURSOR CListCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CListCtrlDlg::InitListCtrl(void)
{
	// 1 ����ͼ���б�
	m_ilNormal.Create(IDB_NORMAL,32,1,RGB(255,255,255));
	m_ilSmall.Create(IDB_SMALL,16,1,RGB(255,255,255));
	// 2 ��ͼ���б����õ��ؼ�
	m_wndList.SetImageList(&m_ilNormal,LVSIL_NORMAL);
	m_wndList.SetImageList(&m_ilSmall,LVSIL_SMALL);
	// 3 ��ӿؼ�����(ֻ�ڱ�����ͼ����ʾ)
	m_wndList.InsertColumn(0,"����",LVCFMT_LEFT,120);
	m_wndList.InsertColumn(1,"��С",LVCFMT_LEFT,80);
	m_wndList.InsertColumn(2,"����",LVCFMT_LEFT,80);
	m_wndList.InsertColumn(3,"�޸�����",LVCFMT_LEFT,150);
	// 4 ����ѡ��
	m_wndList.InsertItem(0,"�����װ��",0);
	m_wndList.SetItemText(0,2,"�ļ���");
	m_wndList.InsertItem(1,"��ҵ���.doc",1);
	m_wndList.InsertItem(2,"day01",0);
	m_wndList.InsertItem(3,"day01�ʼ�.txt",1);
	m_wndList.SetItemText(3,1,"125 k");

	ShowData("c:");
}


void CListCtrlDlg::ShowData(CString strPath)
{
	//������б�ؼ�
	m_wndList.DeleteAllItems();
	//ʹ��CFileFind�࣬��ȡָ��Ŀ¼�µ��ļ�����Ŀ¼���ŵ��б�ؼ�����ʽ
	// InsertItem()��SetItemText()             ��10 ���ӣ�
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
			//��������
			m_wndList.SetItemText(nItem,2,"�ļ���");
		}
		else
		{
			m_wndList.InsertItem(nItem,strName,1);
			// ���ô�С
			ULONGLONG nLen=find.GetLength();
			CString strLen;
			strLen.Format("%lld",nLen);
			m_wndList.SetItemText(nItem,1,strLen);
		}
		CTime t;
		// ����޸�ʱ��
		find.GetLastWriteTime(t);
		CString strTime=t.Format("%Y-%m-%d %H:%M");
		m_wndList.SetItemText(nItem,3,strTime);
		nItem++;

	}
	find.Close();
    
}
