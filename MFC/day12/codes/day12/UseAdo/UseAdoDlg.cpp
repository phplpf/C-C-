
// UseAdoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UseAdo.h"
#include "UseAdoDlg.h"
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


// CUseAdoDlg �Ի���




CUseAdoDlg::CUseAdoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUseAdoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strName = _T("");
	m_nAge = 0;
	m_strAddress = _T("");
	m_strClass = _T("");
	m_strId =  _T("");
}

void CUseAdoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_wndList);
	DDX_Control(pDX, IDC_CLASS, m_wndClass);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_Text(pDX, IDC_AGE, m_nAge);
	DDX_Text(pDX, IDC_ADDRESS, m_strAddress);
	DDX_CBString(pDX, IDC_CLASS, m_strClass);
}

BEGIN_MESSAGE_MAP(CUseAdoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_QUERY, &CUseAdoDlg::OnBnClickedQuery)
	ON_BN_CLICKED(IDC_ADD, &CUseAdoDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DEL, &CUseAdoDlg::OnBnClickedDel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CUseAdoDlg::OnNMDblclkList)
	ON_BN_CLICKED(IDC_MODIFY, &CUseAdoDlg::OnBnClickedModify)
END_MESSAGE_MAP()


// CUseAdoDlg ��Ϣ�������

BOOL CUseAdoDlg::OnInitDialog()
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

	// 1 �������ݿ�
	if (!m_db.OpenAccess("E:/c++1905/stuDB.accdb"))
	{
		AfxMessageBox("���ݿ�����ʧ��");
		PostQuitMessage(0);
	}
	// 2 ��ʼ���༶�ؼ�
	InitClassCtrl();
	// 3 �б�ؼ���չ���(ѡ������)
	m_wndList.SetExtendedStyle(m_wndList.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CUseAdoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUseAdoDlg::OnPaint()
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
HCURSOR CUseAdoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUseAdoDlg::OnBnClickedQuery()
{
	// ��տؼ����к���
	while(m_wndList.DeleteColumn(0));
	m_wndList.DeleteAllItems();
	
	CAdoRecordset set;
	// �򿪼�¼��
	CString strSql="select s.id as ѧԱ���,sname as ����,age as ����,address as ��ַ,cname as �༶���� from student s,class c where s.cid = c.id";

	set.OpenSql(strSql,&m_db);
	long nCount=set.GetFieldCount();
	CString strName;
	for (int i=0;i<nCount;i++)
	{
		set.GetFieldName(i,strName);
		m_wndList.InsertColumn(i,strName,LVCFMT_LEFT,80);
	}
	//��ȡ�ֶε�ֵ�ŵ��б�ؼ�����ʽ(10����)
	CString strValue;
	long nItem=0;
	while (!set.IsEOF())
	{
		for (long i=0;i<nCount;i++)
		{
			set.GetFieldValue(i,strValue);
			if (i==0)
			{
				m_wndList.InsertItem(nItem,strValue);
			} 
			else
			{
				m_wndList.SetItemText(nItem,i,strValue);
			}
		}
		nItem++;
		set.MoveNext();
	}


}


void CUseAdoDlg::InitClassCtrl(void)
{
	CAdoRecordset set;
	set.OpenSql("select id,cname from class",&m_db);
	CString strName;
	CString strId;
	while(!set.IsEOF())
	{
		set.GetFieldValue(0,strId);
		set.GetFieldValue(1,strName);
		long nIndex = m_wndClass.AddString(strName);
		m_wndClass.SetItemData(nIndex,atoi(strId));
		set.MoveNext();
	}
}


void CUseAdoDlg::OnBnClickedAdd()
{
	InsertOrUpdate();
}


void CUseAdoDlg::OnBnClickedDel()
{
	// ɾ������
	POSITION pos =m_wndList.GetFirstSelectedItemPosition();
	if (pos == NULL)return;
	while (pos)
	{
		int nItem =m_wndList.GetNextSelectedItem(pos);
		CString strId=m_wndList.GetItemText(nItem,0);
		CString strSql;
		strSql.Format("delete from student where id=%s",strId);
		m_db.ExecuteSQL(strSql);
	}
	// ���²�ѯ
	OnBnClickedQuery();


}


void CUseAdoDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	long nItem=pNMItemActivate->iItem;
	if (nItem==-1)return;
	m_strId = m_wndList.GetItemText(nItem,0);//ѧԱ���
	m_strName = m_wndList.GetItemText(nItem,1);//����
	m_nAge =atoi(m_wndList.GetItemText(nItem,2)) ;//����
	m_strAddress = m_wndList.GetItemText(nItem,3);//��ַ
	m_strClass = m_wndList.GetItemText(nItem,4);//���ڰ༶
	UpdateData(FALSE);

	*pResult = 0;
}


void CUseAdoDlg::OnBnClickedModify()
{
	InsertOrUpdate(FALSE);
}


void CUseAdoDlg::InsertOrUpdate(BOOL IsInsert)
{
	UpdateData(TRUE);

	int nIndex=m_wndClass.GetCurSel();
	if (nIndex == -1)
	{
		AfxMessageBox("��ѡ�����ڰ༶��");
		return;
	}
	DWORD cid=m_wndClass.GetItemData(nIndex);

	CString strSql;
	if (IsInsert)
	{
		strSql.Format("insert into student(sname,age,address,cid) values('%s',%d,'%s',%d)",
			m_strName,m_nAge,m_strAddress,cid);
	} 
	else
	{
		strSql.Format("update student set sname='%s',age=%d,address='%s',cid=%d where id=%s",
			m_strName,m_nAge,m_strAddress,cid,m_strId);
	}
	m_db.ExecuteSQL(strSql);
	// ���²�ѯ
	OnBnClickedQuery();
}
