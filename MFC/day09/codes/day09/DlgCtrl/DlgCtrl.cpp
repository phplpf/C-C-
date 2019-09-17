#include <afxwin.h>
#include "resource.h"

class CMyDlg:public CDialog
{
public:
	CMyDlg():CDialog(IDD_DIALOG1){}
	virtual BOOL OnInitDialog( ); 
	virtual void DoDataExchange( CDataExchange* pDX );
	virtual void OnOK();
	CButton m_wndOK;//�ؼ����͵ı���
	CString m_strEdit;//ֵ���͵ı���
};
void CMyDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	//��ɿؼ�������İ�
	DDX_Control(pDX,IDOK,m_wndOK);
	DDX_Text(pDX,IDC_EDIT1,m_strEdit);
}
BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// �ؼ��ĳ�ʼ��
    // 1 ��ȡȡ����ť����
	CWnd* pWnd = GetDlgItem(IDCANCEL);
	// 2 ����ȡ����ť���ı�
	pWnd->SetWindowText("ȡ������");

	m_wndOK.SetWindowText("ȷ������");
	m_wndOK.MoveWindow(0,0,100,100);

	m_strEdit = "Hello World";
	//����=>�ؼ�(FALSE)
	UpdateData(FALSE);
	return TRUE;
}
void CMyDlg::OnOK()
{
	UpdateData(TRUE);
	AfxMessageBox(m_strEdit);
}



class CMyWinApp:public CWinApp
{
public:
	virtual BOOL InitInstance();
};
CMyWinApp theApp;
BOOL CMyWinApp::InitInstance()
{
	CMyDlg dlg;
	m_pMainWnd=&dlg;
	dlg.DoModal();
	return TRUE;
}