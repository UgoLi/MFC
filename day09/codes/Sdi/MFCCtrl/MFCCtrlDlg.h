
// MFCCtrlDlg.h : ͷ�ļ�
//

#pragma once


// CMFCCtrlDlg �Ի���
class CMFCCtrlDlg : public CDialogEx
{
// ����
public:
	CMFCCtrlDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCCTRL_DIALOG };

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
	BOOL m_bFlag1;
	BOOL m_bFlag2;
	BOOL m_bFlag3;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CButton m_btnCK1;
	CButton m_btnCK2;
	CButton m_btnCK3;
	int m_nCity;
	afx_msg void OnBnClickedButton3();
};
