
// MyNotePad.h : MyNotePad Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMyNotePadApp:
// �йش����ʵ�֣������ MyNotePad.cpp
//

class CMyNotePadApp : public CWinApp
{
public:
	CMyNotePadApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyNotePadApp theApp;
