// DlgModeless.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Sdi.h"
#include "DlgModeless.h"
#include "afxdialogex.h"


// CDlgModeless �Ի���

IMPLEMENT_DYNAMIC(CDlgModeless, CDialogEx)

CDlgModeless::CDlgModeless(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgModeless::IDD, pParent)
{

}

CDlgModeless::~CDlgModeless()
{
}

void CDlgModeless::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgModeless, CDialogEx)
END_MESSAGE_MAP()


// CDlgModeless ��Ϣ�������


void CDlgModeless::OnOK()
{
	CDialogEx::OnOK();
	DestroyWindow();
}
void CDlgModeless::OnCancel()
{
	CDialogEx::OnCancel();
	DestroyWindow();

}
void CDlgModeless::PostNcDestroy()
{
	CDialogEx::PostNcDestroy();
	delete this;
}
