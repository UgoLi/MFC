
// MFCSdi.h : MFCSdi Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMFCSdiApp:
// �йش����ʵ�֣������ MFCSdi.cpp
//

class CMFCSdiApp : public CWinApp
{
public:
	CMFCSdiApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCSdiApp theApp;
