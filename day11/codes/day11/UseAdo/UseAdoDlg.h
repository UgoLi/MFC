
// UseAdoDlg.h : 头文件
//

#pragma once

#include "AdoDatabase.h"
#include "AdoRecordset.h"
// CUseAdoDlg 对话框
class CUseAdoDlg : public CDialogEx
{
// 构造
public:
	CUseAdoDlg(CWnd* pParent = NULL);	// 标准构造函数
	CAdoDatabase m_db;
// 对话框数据
	enum { IDD = IDD_USEADO_DIALOG };

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
	CString m_strAddress;
	int m_nAge;
	CComboBox m_wndClass;
	CString m_strClass;
	CString m_strName;
	CListCtrl m_wndList;
	afx_msg void OnBnClickedQuery();
};
