// MFCDynCreate.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <afxwin.h>
// 1. ��������ĺ��� (���� RUNTIME_CLASS(����))
CObject* CreateInstance(CRuntimeClass* pClass)
{
	return pClass->CreateObject();
}
// 2. ����֧�ֶ�̬��������
class CAnimal:public CObject
{
DECLARE_DYNCREATE(CAnimal)
};
IMPLEMENT_DYNCREATE(CAnimal,CObject)
class CDog:public CAnimal
{
//DECLARE_DYNCREATE(CDog)
//DECLARE_DYNAMIC(CDog) 
public: 
	static const CRuntimeClass classCDog; 
	virtual CRuntimeClass* GetRuntimeClass() const; 
	static CObject* PASCAL CreateObject();
};
//IMPLEMENT_DYNCREATE(CDog,CAnimal)
CObject* PASCAL CDog::CreateObject() 
{ 
	return new CDog; 
} 
//IMPLEMENT_RUNTIMECLASS(CDog, CAnimal, 0xFFFF, 
//CDog::CreateObject, NULL)
AFX_COMDAT const CRuntimeClass CDog::classCDog = { 
	"CDog", 
	sizeof(class CDog), 
	0xFFFF, 
	CDog::CreateObject, 
	RUNTIME_CLASS(CAnimal),
	NULL,
	NULL
}; 
CRuntimeClass* CDog::GetRuntimeClass() const 
{ 
	return RUNTIME_CLASS(CDog);
}


int _tmain(int argc, _TCHAR* argv[])
{
	// 3. ʹ��
	CObject* pObj = CreateInstance(RUNTIME_CLASS(CDog));
	if(pObj)
	{
		printf("�����ַ��%p\n",pObj);
		printf("�������:%s\n",pObj->GetRuntimeClass()->m_lpszClassName);
	}
	delete pObj;
	pObj = NULL;
	getchar();
	return 0;
}

