
// MFCCommonCtrlDlg.h : ͷ�ļ�
//

#pragma once


// CMFCCommonCtrlDlg �Ի���
class CMFCCommonCtrlDlg : public CDialogEx
{
// ����
public:
	CMFCCommonCtrlDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCCOMMONCTRL_DIALOG };

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
	CSpinButtonCtrl m_wndSpin;
	CSliderCtrl m_wndSlider;
	CProgressCtrl m_wndProgress;
	afx_msg void OnBnClickedMove();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
