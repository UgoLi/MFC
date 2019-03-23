
// MFCODBCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCODBC.h"
#include "MFCODBCDlg.h"
#include "afxdialogex.h"

#include <afxdb.h>


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


// CMFCODBCDlg 对话框




CMFCODBCDlg::CMFCODBCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCODBCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strName = _T("");
}

void CMFCODBCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_wndList);
	DDX_Text(pDX, IDC_NAME, m_strName);
}

BEGIN_MESSAGE_MAP(CMFCODBCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SHOW, &CMFCODBCDlg::OnBnClickedShow)
END_MESSAGE_MAP()


// CMFCODBCDlg 消息处理程序

BOOL CMFCODBCDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCODBCDlg::OnPaint()
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
HCURSOR CMFCODBCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCODBCDlg::OnBnClickedShow()
{
	// 1 连接数据库
	CDatabase db;
	if (!db.Open("TestDB"))
	{
		AfxMessageBox("打开数据源ODBC失败！");
		return;
	}
	// 执行Sql语句
	CString sql="insert into student(SName,Age,Address,cid) values('鲁肃',30,'吴国',3)";
	sql="update student set SName='张翼德' where SName='张飞'";
	sql="delete from student where SName='刘备'";
	db.ExecuteSQL(sql);
	CRecordset set(&db);
	// 2 打开记录集
	UpdateData(TRUE);
	CString strSql;
	if (m_strName=="")
	{
		strSql="select s.id as 学员编号,SName as 学员姓名,Age as 年龄,Address as 地址,CName as 班级名称 from student s,class c where s.cid=c.id";
	} 
	else
	{
		//strSql="select s.id as 学员编号,SName as 学员姓名,Age as 年龄,Address as 地址,CName as 班级名称 from student s,class c where s.cid=c.id and SName='"+m_strName+"'";
		strSql.Format("select s.id as 学员编号,SName as 学员姓名,Age as 年龄,Address as 地址,CName as 班级名称 from student s,class c where s.cid=c.id and SName='%s'",m_strName);
	}


	set.Open(CRecordset::forwardOnly,strSql);
	// 动态添加列之前，首先清空原有列
	while(m_wndList.DeleteColumn(0));
	// 获取记录集中字段的名称作为列表控件的列
	long nCount=set.GetODBCFieldCount();
	CODBCFieldInfo info;
	for (int i=0;i<nCount;i++)
	{
		// 从记录集中获取字段的信息
		set.GetODBCFieldInfo(i,info);
		m_wndList.InsertColumn(i,info.m_strName,LVCFMT_LEFT,80);
	}
	// 获取记录集中的数据放到列表控件中显示
	m_wndList.DeleteAllItems();//清空原有数据
	CString strValue;
	int nItem=0;//列表控件中行的索引值
	while (!set.IsEOF())
	{
		for (int i=0;i<nCount;i++)
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

	// 关闭记录集
	set.Close(); 
	// 关闭数据库
	db.Close();
}
