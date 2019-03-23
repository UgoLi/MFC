
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
	InitClassCtrl();
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
	
	CString sql="select s.id as ѧԱ���,SName as ѧԱ����,Age as ����,Address as ��ַ,CName as �༶���� from student s,class c where s.cid=c.id";
	set.OpenSql(sql,&m_db);
	int nCount=set.GetFieldCount();
	CString strName;
	for (int i=0;i<nCount;i++)
	{
		set.GetFieldName(i,strName);
		m_wndList.InsertColumn(i,strName,LVCFMT_LEFT,90);
	}
	// 3 �Ӽ�¼���л�ȡ�ֶε�ֵ�ŵ��б�ؼ�����ʾ(10����)
	//����¼����ָ��û���ƶ�����βʱ
	CString strValue;
	long nItem=0;//�б�ؼ����е�����ֵ
	while(!set.IsEOF())
	{
		for (int i=0;i<nCount;i++)
		{
			set.GetFieldValue(i,strValue);
			if (0==i)//��һ��
			{
				m_wndList.InsertItem(nItem,strValue);
			} 
			else
			{
				m_wndList.SetItemText(nItem,i,strValue);
			}
		}
		nItem++;
		//�ƶ�����һ����¼
		set.MoveNext();
	}
}


// ��ʼ���༶��Ͽ�ؼ�
void CUseAdoDlg::InitClassCtrl(void)
{
	CAdoRecordset set;
	set.OpenSql("select id,CName from class",&m_db);
	CString strID;
	CString strName;
	while(!set.IsEOF())
	{
		// ��ȡ�༶�ı��
		set.GetFieldValue(0,strID);
		// ��ȡ�༶����
		set.GetFieldValue(1,strName);
		// ���༶���Ʊ���Ϊ����Ͽ�ؼ���ѡ��
		int index=m_wndClass.AddString(strName);
		// ���༶��ű���Ϊ��Ͽ�ؼ�ѡ��ĸ���������
		m_wndClass.SetItemData(index,atoi(strID));
		set.MoveNext();
	}
}


void CUseAdoDlg::OnBnClickedIns()
{
	// 1 ��ȡ�û����������
	UpdateData(TRUE);
	// ���û�ѡ���˰༶֮�󣬻�ȡ�༶���
	int nSel=m_wndClass.GetCurSel();
	if (nSel==-1)
	{
		AfxMessageBox("��ѡ�����ڰ༶��");
		return;
	}
	// ��������ֵ����ȡ��������
	DWORD cid=m_wndClass.GetItemData(nSel);
	// 2 ƴ�Ӳ�������sql
	CString strSql;
	strSql.Format("insert into student(SName,Age,Address,cid) values('%s',%d,'%s',%d)",
		m_strName,m_nAge,m_strAddress,cid);
	m_db.OpenSql(strSql);
	// 3 ���²�ѯ
	OnBnClickedQuery();
}


void CUseAdoDlg::OnBnClickedDel()
{
	// ����ѧԱ���ɾ��ָ��ѧԱ
	// 1 ��ȡ�û�ѡ����
	POSITION pos = m_wndList.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		AfxMessageBox("��ѡ��Ҫɾ����ѧԱ");
		return;
	}
	int nItem = m_wndList.GetNextSelectedItem(pos);
	// 2 ��������ֵ��ȡѧԱ���
	CString strID=m_wndList.GetItemText(nItem,0);
	//AfxMessageBox(strID);
	// 3 ƴ��ɾ����sql���
	CString strSql;
	strSql.Format("delete from student where id=%s",strID);
	// 4 ִ��ɾ������
	m_db.OpenSql(strSql);
	// 5 ���²�ѯ
	OnBnClickedQuery();
		

}


void CUseAdoDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// ˫��ĳһ��ѡ��ʱ����һ���е����ݴ��ݸ����������û����ݵĿؼ�
	int nItem=pNMItemActivate->iItem;
	if (nItem==-1)return;
	
	m_strID=m_wndList.GetItemText(nItem,0);//���
	m_strName= m_wndList.GetItemText(nItem,1);//����
	m_nAge=atoi(m_wndList.GetItemText(nItem,2));//����
	m_strAddress=m_wndList.GetItemText(nItem,3);//��ַ
	m_strClass=m_wndList.GetItemText(nItem,4);//�༶����

	// ��������ֵ�ŵ��ؼ�����ʾ
	UpdateData(FALSE);
	
	*pResult = 0;
}


void CUseAdoDlg::OnBnClickedMod()
{
	if (m_strID.IsEmpty())return;
	// ��ȡ�û����������
	UpdateData(TRUE);
	// ���û�ѡ���˰༶֮�󣬻�ȡ�༶���
	int nSel=m_wndClass.GetCurSel();
	if (nSel==-1)
	{
		AfxMessageBox("��ѡ�����ڰ༶��");
		return;
	}
	// ��������ֵ����ȡ��������
	DWORD cid=m_wndClass.GetItemData(nSel);
	// ƴ���޸ĵ�Sql���
	CString strSql;
	strSql.Format("update student set SName='%s',age=%d,address='%s',cid=%d where id=%s",
		m_strName,m_nAge,m_strAddress,cid,m_strID);
	m_db.OpenSql(strSql);
	// ���²�ѯ
	OnBnClickedQuery();

}
