#include <afxwin.h>
#include "resource.h"
// 1 �Ի���
class CMyDlg:public CDialog
{
public:
	CMyDlg():CDialog(IDD_DIALOG1){}
	//�Ի���ĳ�ʼ������
	virtual BOOL OnInitDialog( );
	// ������ؼ��İ�
	virtual void DoDataExchange( CDataExchange* pDX );
	virtual void OnOK();

public:
	CButton m_wndOK;//�ؼ����͵ĳ�Ա����
	CString m_strEdit;//ֵ���͵ĳ�Ա����
};
void CMyDlg::OnOK()
{
	UpdateData(TRUE);
	AfxMessageBox(m_strEdit);
}
void CMyDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	// �ؼ�������İ�
	DDX_Control(pDX,IDOK,m_wndOK);
	DDX_Text(pDX,IDC_EDIT1,m_strEdit);
}
BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// �ؼ��ĳ�ʼ��
	// ��ȡ����ť���ı��޸�Ϊȡ������
	CWnd* pWnd=GetDlgItem(IDCANCEL);
	pWnd->SetWindowText("ȡ������");
	// ��ȷ�����ı��޸�Ϊִ�в���
	m_wndOK.SetWindowText("ִ�в���");
	// �޸�ȷ����ť��λ�ô�С
	m_wndOK.MoveWindow(0,0,100,40);

	// ���༭�ؼ��ĳ�ʼֵ��ΪHelloWorld
	m_strEdit="HelloWorld";
	UpdateData(FALSE);
	return TRUE;
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