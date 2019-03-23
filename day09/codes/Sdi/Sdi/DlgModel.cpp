// DlgModel.cpp : 实现文件
//

#include "stdafx.h"
#include "Sdi.h"
#include "DlgModel.h"
#include "afxdialogex.h"


// CDlgModel 对话框

IMPLEMENT_DYNAMIC(CDlgModel, CDialogEx)

CDlgModel::CDlgModel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgModel::IDD, pParent)
{

}

CDlgModel::~CDlgModel()
{
}

void CDlgModel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgModel, CDialogEx)
END_MESSAGE_MAP()


// CDlgModel 消息处理程序
