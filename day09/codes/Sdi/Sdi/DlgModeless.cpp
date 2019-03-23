// DlgModeless.cpp : 实现文件
//

#include "stdafx.h"
#include "Sdi.h"
#include "DlgModeless.h"
#include "afxdialogex.h"


// CDlgModeless 对话框

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


// CDlgModeless 消息处理程序


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
