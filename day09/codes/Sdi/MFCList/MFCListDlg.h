
// MFCListDlg.h : ͷ�ļ�
//

#pragma once


// CMFCListDlg �Ի���
class CMFCListDlg : public CDialogEx
{
// ����
public:
	CMFCListDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCLIST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_wndList1;
	CListBox m_wndList2;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
