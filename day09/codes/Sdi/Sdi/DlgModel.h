#pragma once


// CDlgModel �Ի���

class CDlgModel : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgModel)

public:
	CDlgModel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgModel();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
