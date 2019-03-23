
// MFCCtrlDlg.h : 头文件
//

#pragma once


// CMFCCtrlDlg 对话框
class CMFCCtrlDlg : public CDialogEx
{
// 构造
public:
	CMFCCtrlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCCTRL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
