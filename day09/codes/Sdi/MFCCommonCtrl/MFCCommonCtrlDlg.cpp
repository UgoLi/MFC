
// MFCCommonCtrlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCCommonCtrl.h"
#include "MFCCommonCtrlDlg.h"
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


// CMFCCommonCtrlDlg 对话框




CMFCCommonCtrlDlg::CMFCCommonCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCCommonCtrlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCCommonCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPIN1, m_wndSpin);
	DDX_Control(pDX, IDC_SLIDER1, m_wndSlider);
	DDX_Control(pDX, IDC_PROGRESS2, m_wndProgress);
}

BEGIN_MESSAGE_MAP(CMFCCommonCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MOVE, &CMFCCommonCtrlDlg::OnBnClickedMove)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CMFCCommonCtrlDlg 消息处理程序

BOOL CMFCCommonCtrlDlg::OnInitDialog()
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

	// 1 设置数值范围
	m_wndSpin.SetRange(0,1000);
	m_wndSlider.SetRange(0,1000);
	m_wndProgress.SetRange(0,1000);
	// 2 设置增量
	UDACCEL accel[2];
	accel[0].nInc=5;
	accel[0].nSec=1;
	accel[1].nInc=50;
	accel[1].nSec=2;
	m_wndSpin.SetAccel(2,accel);
	// 设置进度条的步长
	m_wndProgress.SetStep(100);
	// 设置滑块的增量
	m_wndSlider.SetLineSize(100);
	m_wndSlider.SetPageSize(200);
	// 设置滑块的刻度
	m_wndSlider.SetTicFreq(100);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCCommonCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCCommonCtrlDlg::OnPaint()
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
HCURSOR CMFCCommonCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCCommonCtrlDlg::OnBnClickedMove()
{
	// 1 进度条前进一个步长
	m_wndProgress.StepIt();
	// 2 获取进度条的当前位置，设置给旋转按钮
	int nPos=m_wndProgress.GetPos();
	m_wndSpin.SetPos(nPos);
	m_wndSlider.SetPos(nPos);

}


void CMFCCommonCtrlDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(((CSliderCtrl*)pScrollBar)==&m_wndSlider)
	{
		int nPos=m_wndSlider.GetPos();
		m_wndSpin.SetPos(nPos);
		m_wndProgress.SetPos(nPos);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CMFCCommonCtrlDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(((CSpinButtonCtrl*)pScrollBar)==&m_wndSpin)
	{
		int nPos=m_wndSpin.GetPos();
		m_wndSlider.SetPos(nPos);
		m_wndProgress.SetPos(nPos);
	}
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}
