
// UseAdoDlg.h : ͷ�ļ�
//

#pragma once

#include "AdoDatabase.h"
#include "AdoRecordset.h"
// CUseAdoDlg �Ի���
class CUseAdoDlg : public CDialogEx
{
// ����
public:
	CUseAdoDlg(CWnd* pParent = NULL);	// ��׼���캯��
	CAdoDatabase m_db;
// �Ի�������
	enum { IDD = IDD_USEADO_DIALOG };

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
	CString m_strAddress;
	int m_nAge;
	CComboBox m_wndClass;
	CString m_strClass;
	CString m_strName;
	CListCtrl m_wndList;
	afx_msg void OnBnClickedQuery();
};
