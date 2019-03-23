
// UseAdoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UseAdo.h"
#include "UseAdoDlg.h"
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


// CUseAdoDlg �Ի���




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


// CUseAdoDlg ��Ϣ�������

BOOL CUseAdoDlg::OnInitDialog()
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	// 1 �������ݿ�
	if (!m_db.OpenAccess("E:/csd1810/stuDB.accdb"))
	{
		AfxMessageBox("�����ݿ�ʧ�ܣ�");
		PostQuitMessage(0);
	}
	// 2 �ؼ��ĳ�ʼ��

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUseAdoDlg::OnPaint()
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
HCURSOR CUseAdoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUseAdoDlg::OnBnClickedQuery()
{
	//1 ����б�ؼ����к���
	m_wndList.DeleteAllItems();
	while(m_wndList.DeleteColumn(0));
	// 2 �Ӽ�¼����ȡ�ֶε�������ӵ��б�ؼ���
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
