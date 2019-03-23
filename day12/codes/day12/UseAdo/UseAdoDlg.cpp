
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
	m_strID=_T("");
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
	ON_BN_CLICKED(IDC_INS, &CUseAdoDlg::OnBnClickedIns)
	ON_BN_CLICKED(IDC_DEL, &CUseAdoDlg::OnBnClickedDel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CUseAdoDlg::OnNMDblclkList)
	ON_BN_CLICKED(IDC_MOD, &CUseAdoDlg::OnBnClickedMod)
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
	InitClassCtrl();
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
	
	CString sql="select s.id as 学员编号,SName as 学员姓名,Age as 年龄,Address as 地址,CName as 班级名称 from student s,class c where s.cid=c.id";
	set.OpenSql(sql,&m_db);
	int nCount=set.GetFieldCount();
	CString strName;
	for (int i=0;i<nCount;i++)
	{
		set.GetFieldName(i,strName);
		m_wndList.InsertColumn(i,strName,LVCFMT_LEFT,90);
	}
	// 3 从记录集中获取字段的值放到列表控件中显示(10分钟)
	//当记录集的指针没有移动到结尾时
	CString strValue;
	long nItem=0;//列表控件中行的索引值
	while(!set.IsEOF())
	{
		for (int i=0;i<nCount;i++)
		{
			set.GetFieldValue(i,strValue);
			if (0==i)//第一列
			{
				m_wndList.InsertItem(nItem,strValue);
			} 
			else
			{
				m_wndList.SetItemText(nItem,i,strValue);
			}
		}
		nItem++;
		//移动到下一条记录
		set.MoveNext();
	}
}


// 初始化班级组合框控件
void CUseAdoDlg::InitClassCtrl(void)
{
	CAdoRecordset set;
	set.OpenSql("select id,CName from class",&m_db);
	CString strID;
	CString strName;
	while(!set.IsEOF())
	{
		// 获取班级的编号
		set.GetFieldValue(0,strID);
		// 获取班级名称
		set.GetFieldValue(1,strName);
		// 将班级名称保存为到组合框控件的选项
		int index=m_wndClass.AddString(strName);
		// 将班级编号保存为组合框控件选项的附加数据中
		m_wndClass.SetItemData(index,atoi(strID));
		set.MoveNext();
	}
}


void CUseAdoDlg::OnBnClickedIns()
{
	// 1 获取用户输入的数据
	UpdateData(TRUE);
	// 当用户选择了班级之后，获取班级编号
	int nSel=m_wndClass.GetCurSel();
	if (nSel==-1)
	{
		AfxMessageBox("请选择所在班级！");
		return;
	}
	// 根据索引值，获取附加数据
	DWORD cid=m_wndClass.GetItemData(nSel);
	// 2 拼接插入语句的sql
	CString strSql;
	strSql.Format("insert into student(SName,Age,Address,cid) values('%s',%d,'%s',%d)",
		m_strName,m_nAge,m_strAddress,cid);
	m_db.OpenSql(strSql);
	// 3 重新查询
	OnBnClickedQuery();
}


void CUseAdoDlg::OnBnClickedDel()
{
	// 根据学员编号删除指定学员
	// 1 获取用户选择项
	POSITION pos = m_wndList.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		AfxMessageBox("请选择要删除的学员");
		return;
	}
	int nItem = m_wndList.GetNextSelectedItem(pos);
	// 2 根据索引值获取学员编号
	CString strID=m_wndList.GetItemText(nItem,0);
	//AfxMessageBox(strID);
	// 3 拼接删除的sql语句
	CString strSql;
	strSql.Format("delete from student where id=%s",strID);
	// 4 执行删除操作
	m_db.OpenSql(strSql);
	// 5 重新查询
	OnBnClickedQuery();
		

}


void CUseAdoDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// 双击某一个选项时，将一整行的数据传递给其它接收用户数据的控件
	int nItem=pNMItemActivate->iItem;
	if (nItem==-1)return;
	
	m_strID=m_wndList.GetItemText(nItem,0);//编号
	m_strName= m_wndList.GetItemText(nItem,1);//姓名
	m_nAge=atoi(m_wndList.GetItemText(nItem,2));//年龄
	m_strAddress=m_wndList.GetItemText(nItem,3);//地址
	m_strClass=m_wndList.GetItemText(nItem,4);//班级名称

	// 将变量的值放到控件上显示
	UpdateData(FALSE);
	
	*pResult = 0;
}


void CUseAdoDlg::OnBnClickedMod()
{
	if (m_strID.IsEmpty())return;
	// 获取用户输入的数据
	UpdateData(TRUE);
	// 当用户选择了班级之后，获取班级编号
	int nSel=m_wndClass.GetCurSel();
	if (nSel==-1)
	{
		AfxMessageBox("请选择所在班级！");
		return;
	}
	// 根据索引值，获取附加数据
	DWORD cid=m_wndClass.GetItemData(nSel);
	// 拼接修改的Sql语句
	CString strSql;
	strSql.Format("update student set SName='%s',age=%d,address='%s',cid=%d where id=%s",
		m_strName,m_nAge,m_strAddress,cid,m_strID);
	m_db.OpenSql(strSql);
	// 重新查询
	OnBnClickedQuery();

}
