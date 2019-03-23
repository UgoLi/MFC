
// MFCCommonCtrlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCCommonCtrl.h"
#include "MFCCommonCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFCCommonCtrlDlg �Ի���




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


// CMFCCommonCtrlDlg ��Ϣ�������

BOOL CMFCCommonCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// 1 ������ֵ��Χ
	m_wndSpin.SetRange(0,1000);
	m_wndSlider.SetRange(0,1000);
	m_wndProgress.SetRange(0,1000);
	// 2 ��������
	UDACCEL accel[2];
	accel[0].nInc=5;
	accel[0].nSec=1;
	accel[1].nInc=50;
	accel[1].nSec=2;
	m_wndSpin.SetAccel(2,accel);
	// ���ý������Ĳ���
	m_wndProgress.SetStep(100);
	// ���û��������
	m_wndSlider.SetLineSize(100);
	m_wndSlider.SetPageSize(200);
	// ���û���Ŀ̶�
	m_wndSlider.SetTicFreq(100);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCCommonCtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCCommonCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCCommonCtrlDlg::OnBnClickedMove()
{
	// 1 ������ǰ��һ������
	m_wndProgress.StepIt();
	// 2 ��ȡ�������ĵ�ǰλ�ã����ø���ת��ť
	int nPos=m_wndProgress.GetPos();
	m_wndSpin.SetPos(nPos);
	m_wndSlider.SetPos(nPos);

}


void CMFCCommonCtrlDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(((CSpinButtonCtrl*)pScrollBar)==&m_wndSpin)
	{
		int nPos=m_wndSpin.GetPos();
		m_wndSlider.SetPos(nPos);
		m_wndProgress.SetPos(nPos);
	}
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}
