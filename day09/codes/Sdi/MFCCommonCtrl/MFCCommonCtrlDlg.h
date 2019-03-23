
// MFCCommonCtrlDlg.h : 头文件
//

#pragma once


// CMFCCommonCtrlDlg 对话框
class CMFCCommonCtrlDlg : public CDialogEx
{
// 构造
public:
	CMFCCommonCtrlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCCOMMONCTRL_DIALOG };

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
	CSpinButtonCtrl m_wndSpin;
	CSliderCtrl m_wndSlider;
	CProgressCtrl m_wndProgress;
	afx_msg void OnBnClickedMove();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
