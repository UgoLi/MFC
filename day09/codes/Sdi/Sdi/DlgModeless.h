#pragma once


// CDlgModeless �Ի���

class CDlgModeless : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgModeless)

public:
	CDlgModeless(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgModeless();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
	virtual void PostNcDestroy();
};
