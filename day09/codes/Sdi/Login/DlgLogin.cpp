// DlgLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Login.h"
#include "DlgLogin.h"
#include "afxdialogex.h"


// CDlgLogin �Ի���

IMPLEMENT_DYNAMIC(CDlgLogin, CDialogEx)

CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLogin::IDD, pParent)
{

	m_strName = _T("");
	m_strPwd = _T("");
}

CDlgLogin::~CDlgLogin()
{
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME, m_strName);
	//  DDX_Control(pDX, IDC_PWD, m_strPwd);
	DDX_Text(pDX, IDC_PWD, m_strPwd);
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgLogin::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgLogin ��Ϣ�������


void CDlgLogin::OnBnClickedOk()
{
	// ��֤��name:csd1810,pwd:best
	UpdateData(TRUE);
	if (m_strName=="csd1810"&&m_strPwd=="best")
	{
		CDialogEx::OnOK();
	} 
	else
	{
		AfxMessageBox("�û����ƻ������������������");
	}
	
}
