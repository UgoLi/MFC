
// MFCServerDlg.h : ͷ�ļ�
//

#pragma once

#include "ServerSocket.h"
// CMFCServerDlg �Ի���
class CMFCServerDlg : public CDialogEx
{
// ����
public:
	CMFCServerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	CServerSocket m_server;
// �Ի�������
	enum { IDD = IDD_MFCSERVER_DIALOG };

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
	afx_msg void OnBnClickedStart();
};
