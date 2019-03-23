
// MFCODBCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCODBC.h"
#include "MFCODBCDlg.h"
#include "afxdialogex.h"

#include <afxdb.h>


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


// CMFCODBCDlg �Ի���




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


// CMFCODBCDlg ��Ϣ�������

BOOL CMFCODBCDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCODBCDlg::OnPaint()
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
HCURSOR CMFCODBCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCODBCDlg::OnBnClickedShow()
{
	// 1 �������ݿ�
	CDatabase db;
	if (!db.Open("TestDB"))
	{
		AfxMessageBox("������ԴODBCʧ�ܣ�");
		return;
	}
	// ִ��Sql���
	CString sql="insert into student(SName,Age,Address,cid) values('³��',30,'���',3)";
	sql="update student set SName='�����' where SName='�ŷ�'";
	sql="delete from student where SName='����'";
	db.ExecuteSQL(sql);
	CRecordset set(&db);
	// 2 �򿪼�¼��
	UpdateData(TRUE);
	CString strSql;
	if (m_strName=="")
	{
		strSql="select s.id as ѧԱ���,SName as ѧԱ����,Age as ����,Address as ��ַ,CName as �༶���� from student s,class c where s.cid=c.id";
	} 
	else
	{
		//strSql="select s.id as ѧԱ���,SName as ѧԱ����,Age as ����,Address as ��ַ,CName as �༶���� from student s,class c where s.cid=c.id and SName='"+m_strName+"'";
		strSql.Format("select s.id as ѧԱ���,SName as ѧԱ����,Age as ����,Address as ��ַ,CName as �༶���� from student s,class c where s.cid=c.id and SName='%s'",m_strName);
	}


	set.Open(CRecordset::forwardOnly,strSql);
	// ��̬�����֮ǰ���������ԭ����
	while(m_wndList.DeleteColumn(0));
	// ��ȡ��¼�����ֶε�������Ϊ�б�ؼ�����
	long nCount=set.GetODBCFieldCount();
	CODBCFieldInfo info;
	for (int i=0;i<nCount;i++)
	{
		// �Ӽ�¼���л�ȡ�ֶε���Ϣ
		set.GetODBCFieldInfo(i,info);
		m_wndList.InsertColumn(i,info.m_strName,LVCFMT_LEFT,80);
	}
	// ��ȡ��¼���е����ݷŵ��б�ؼ�����ʾ
	m_wndList.DeleteAllItems();//���ԭ������
	CString strValue;
	int nItem=0;//�б�ؼ����е�����ֵ
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

	// �رռ�¼��
	set.Close(); 
	// �ر����ݿ�
	db.Close();
}
