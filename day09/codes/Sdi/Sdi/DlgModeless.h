#pragma once


// CDlgModeless 对话框

class CDlgModeless : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgModeless)

public:
	CDlgModeless(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgModeless();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
	virtual void PostNcDestroy();
};
