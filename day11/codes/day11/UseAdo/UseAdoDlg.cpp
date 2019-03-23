
// UseAdoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UseAdo.h"
#include "UseAdoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CUseAdoDlg 对话框




CUseAdoDlg::CUseAdoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUseAdoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strAddress = _T("");
	m_nAge = 0;
	m_strClass = _T("");
	m_strName = _T("");
}

void CUseAdoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ADDRESS, m_strAddress);
	DDX_Text(pDX, IDC_AGE, m_nAge);
	DDX_Control(pDX, IDC_CLASS, m_wndClass);
	DDX_CBString(pDX, IDC_CLASS, m_strClass);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_Control(pDX, IDC_LIST, m_wndList);
}

BEGIN_MESSAGE_MAP(CUseAdoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_QUERY, &CUseAdoDlg::OnBnClickedQuery)
END_MESSAGE_MAP()


// CUseAdoDlg 消息处理程序

BOOL CUseAdoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	// 1 连接数据库
	if (!m_db.OpenAccess("E:/csd1810/stuDB.accdb"))
	{
		AfxMessageBox("打开数据库失败！");
		PostQuitMessage(0);
	}
	// 2 控件的初始化

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUseAdoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CUseAdoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUseAdoDlg::OnBnClickedQuery()
{
	//1 清空列表控件的行和列
	m_wndList.DeleteAllItems();
	while(m_wndList.DeleteColumn(0));
	// 2 从记录集获取字段的名称添加到列表控件上
	CAdoRecordset set;
	set.OpenSql("select * from student",&m_db);
	int nCount=set.GetFieldCount();
	CString strName;
	for (int i=0;i<nCount;i++)
	{
		set.GetFieldName(i,strName);
		m_wndList.InsertColumn(i,strName,LVCFMT_LEFT,90);
	}
}
