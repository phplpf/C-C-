
// TreeCtrlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TreeCtrl.h"
#include "TreeCtrlDlg.h"
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


// CTreeCtrlDlg �Ի���




CTreeCtrlDlg::CTreeCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTreeCtrlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strName = _T("");
}

void CTreeCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_wndTree);
	DDX_Text(pDX, IDC_NAME, m_strName);
}

BEGIN_MESSAGE_MAP(CTreeCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTreeCtrlDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CTreeCtrlDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CTreeCtrlDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CTreeCtrlDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CTreeCtrlDlg ��Ϣ�������

BOOL CTreeCtrlDlg::OnInitDialog()
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

	// 1 �������ؼ���ͼ���б�
	m_ilNormal.Create(IDB_NORMAL,16,1,RGB(255,255,255));
	m_wndTree.SetImageList(&m_ilNormal,TVSIL_NORMAL);
	
	// 2 ���ýڵ�߶�
	m_wndTree.SetItemHeight(25);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTreeCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTreeCtrlDlg::OnPaint()
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
HCURSOR CTreeCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTreeCtrlDlg::OnBnClickedButton1()
{
	// 1 ������ڵ�
	UpdateData(TRUE);
	m_wndTree.InsertItem(m_strName,0,1);
}


void CTreeCtrlDlg::OnBnClickedButton3()
{
	// 2 �����ӽڵ�
	
	UpdateData(TRUE);
	// 1 ��ȡ��ǰѡ�нڵ�
	HTREEITEM hItem=m_wndTree.GetSelectedItem();
	if (hItem==NULL)return;
	// 2 �����ӽڵ�
	m_wndTree.InsertItem(m_strName,0,1,hItem);
	// 3 չ��ѡ�нڵ�
	m_wndTree.Expand(hItem,TVE_EXPAND);

}


void CTreeCtrlDlg::OnBnClickedButton2()
{
	// ɾ���ڵ�
	// 1 ��ȡҪɾ���Ľڵ�
	HTREEITEM hItem = m_wndTree.GetSelectedItem();
	if (hItem==NULL)return;
	// 2 �жϵ�ǰ�ڵ����Ƿ����ӽڵ�
	if(m_wndTree.ItemHasChildren(hItem))
	{
		AfxMessageBox("����ɾ���ӽڵ㣬��ɾ���ýڵ㣡");
		return;
	}
	// 3   ɾ���ڵ�
	m_wndTree.DeleteItem(hItem);
}


void CTreeCtrlDlg::OnBnClickedButton4()
{
	// ���½ڵ�
	// 1 ��ȡ�û�����
	UpdateData(TRUE);
	// 2 ��ȡ��ǰѡ�нڵ�
	HTREEITEM hItem=m_wndTree.GetSelectedItem();
	if (hItem==NULL)return;
	// 3 ���½ڵ��ı�
	m_wndTree.SetItemText(hItem,m_strName);
}
