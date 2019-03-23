#pragma once


// CDlgModel 对话框

class CDlgModel : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgModel)

public:
	CDlgModel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgModel();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
