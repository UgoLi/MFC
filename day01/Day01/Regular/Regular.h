// Regular.h : Regular DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRegularApp
// �йش���ʵ�ֵ���Ϣ������� Regular.cpp
//

class CRegularApp : public CWinApp
{
public:
	CRegularApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
