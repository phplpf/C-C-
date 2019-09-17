
// MFCODBCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCODBC.h"
#include "MFCODBCDlg.h"
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


// CMFCODBCDlg �Ի���




CMFCODBCDlg::CMFCODBCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCODBCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strName = _T("");
	m_nAge = 0;
	m_strAddress = _T("");
	m_strId= _T("");
	m_strClass = _T("");
}

void CMFCODBCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_wndList);
	DDX_Control(pDX, IDC_CLASS, m_wndClass);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_Text(pDX, IDC_AGE, m_nAge);
	DDX_Text(pDX, IDC_ADDRESS, m_strAddress);
	DDX_CBString(pDX, IDC_CLASS, m_strClass);
}

BEGIN_MESSAGE_MAP(CMFCODBCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_QUERY, &CMFCODBCDlg::OnBnClickedQuery)
	ON_BN_CLICKED(IDC_ADD, &CMFCODBCDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DEL, &CMFCODBCDlg::OnBnClickedDel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CMFCODBCDlg::OnNMDblclkList)
	ON_BN_CLICKED(IDC_MODIFY, &CMFCODBCDlg::OnBnClickedModify)
END_MESSAGE_MAP()


// CMFCODBCDlg ��Ϣ�������

BOOL CMFCODBCDlg::OnInitDialog()
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
	// 1 �������ݿ�
	if (!m_db.Open("testDB"))
	{
		AfxMessageBox("�������ݿ�ʧ�ܣ�");
		return TRUE;
	}
	// 2 ��ʼ���༶�ؼ�
	InitClassCtrl();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCODBCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCODBCDlg::OnPaint()
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
HCURSOR CMFCODBCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCODBCDlg::OnClose()
{
	// �ر����ݿ� 
	m_db.Close();
	CDialogEx::OnClose();
}


void CMFCODBCDlg::OnBnClickedQuery()
{
	CRecordset set(&m_db);
	// 1�򿪼�¼��
	CString strSql="select s.id as ѧԱ���,sname as ����,age as ����,address as ��ַ,cname as ���ڰ༶ from student s,class c where s.cid=c.id";
	set.Open(CRecordset::forwardOnly,strSql);
	// �����֮ǰ������տؼ���ԭ�е���
	while(m_wndList.DeleteColumn(0));
	// 2 ��ȡ�ֶε�����
	long nCount=set.GetODBCFieldCount();
	CODBCFieldInfo info;//����ÿ���ֶε���Ϣ(���а������ֶε�����)
	for (int i=0;i<nCount;i++)
	{
		set.GetODBCFieldInfo(i,info);
		m_wndList.InsertColumn(i,info.m_strName,LVCFMT_LEFT,80);
	}
	// �������֮ǰ����Ҫ���ԭ������
	m_wndList.DeleteAllItems();
	CString strValue;
	long nItem=0;
	while(!set.IsEOF())
	{
		for (int i=0;i<nCount;i++)
		{
			set.GetFieldValue(i,strValue);
			if (i == 0)
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


void CMFCODBCDlg::InitClassCtrl(void)
{
	CRecordset set(&m_db);
	set.Open(CRecordset::forwardOnly,"select id,cname from class");
	CString strId;
	CString strName;
	while(!set.IsEOF())
	{
		set.GetFieldValue((short)0,strId);
		set.GetFieldValue(1,strName);
		long nIndex=m_wndClass.AddString(strName);
		m_wndClass.SetItemData(nIndex,atoi(strId));
		set.MoveNext();
	}
}


void CMFCODBCDlg::OnBnClickedAdd()
{
	UpdateData(TRUE);

	int nIndex=m_wndClass.GetCurSel();
	if (nIndex == -1)
	{
		AfxMessageBox("��ѡ�����ڰ༶��");
		return;
	}
	DWORD cid=m_wndClass.GetItemData(nIndex);
	// �����ݿ��в���һ����¼
	CString strSql;
	//ƴ��Sql���(���û��ڿؼ��������ֵ��ϵ�Sql�����)
   strSql.Format("insert into student(sname,age,address,cid) values('%s',%d,'%s',%d)",
	   m_strName,m_nAge,m_strAddress,cid);
   	m_db.ExecuteSQL(strSql);
	// ���²�ѯ
	OnBnClickedQuery();
}


void CMFCODBCDlg::OnBnClickedDel()
{
	POSITION pos = m_wndList.GetFirstSelectedItemPosition();
	if (pos == NULL)return;
	while (pos)
	{
		int nItem = m_wndList.GetNextSelectedItem(pos);
		CString strId=m_wndList.GetItemText(nItem,0);
		CString strSql;
		strSql.Format("delete from student where id=%s",strId);
		m_db.ExecuteSQL(strSql);
	}
	// ���²�ѯ
	OnBnClickedQuery();


}


void CMFCODBCDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nItem=pNMItemActivate->iItem;
	if (nItem == -1)return;
	m_strId =m_wndList.GetItemText(nItem,0);//���
	m_strName = m_wndList.GetItemText(nItem,1);//����
	m_nAge = atoi(m_wndList.GetItemText(nItem,2));//����
	m_strAddress = m_wndList.GetItemText(nItem,3);//��ַ
	m_strClass =m_wndList.GetItemText(nItem,4);//�༶����

	UpdateData(FALSE);

	*pResult = 0;
}


void CMFCODBCDlg::OnBnClickedModify()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int nIndex=m_wndClass.GetCurSel();
	if (nIndex == -1)
	{
		AfxMessageBox("��ѡ�����ڰ༶��");
		return;
	}
	DWORD cid=m_wndClass.GetItemData(nIndex);
	CString strSql;
	strSql.Format("update student set sname='%s',age=%d,address='%s',cid=%d where id=%s",
		m_strName,m_nAge,m_strAddress,cid,m_strId);
	m_db.ExecuteSQL(strSql);
	// ���²�ѯ
	OnBnClickedQuery();
}
