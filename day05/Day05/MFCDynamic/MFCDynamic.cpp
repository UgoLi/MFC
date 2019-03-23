// MFCDynamic.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <afxwin.h>
// 1. ����֧������ʱ����Ϣ����
class CAnimal:public CObject
{
DECLARE_DYNAMIC(CAnimal)
};
IMPLEMENT_DYNAMIC(CAnimal,CObject)
class CDog:public CAnimal
{
//DECLARE_DYNAMIC(CDog)
public: 
	static const CRuntimeClass classCDog; 
	virtual CRuntimeClass* GetRuntimeClass() const; 
};
//IMPLEMENT_DYNAMIC(CDog,CAnimal)
//IMPLEMENT_RUNTIMECLASS(CDog, CAnimal, 0xFFFF, NULL, NULL)
AFX_COMDAT const CRuntimeClass CDog::classCDog = { 
	"CDog", 
	sizeof(class CDog),
	0xFFFF,
	NULL, 
	((CRuntimeClass*)(&CAnimal::classCAnimal)),
	NULL,
	NULL
}; 
CRuntimeClass* CDog::GetRuntimeClass() const 
{ 
	return ((CRuntimeClass*)(&CDog::classCDog)); 
}


int _tmain(int argc, _TCHAR* argv[])
{
	CDog dog;
	// CRuntimeClass*  
	if(dog.IsKindOf(RUNTIME_CLASS(CObject)))
	{
		printf("dog is a CObject\n");
	}
	else
	{
		printf("dog is not a CObject\n");
	}
	getchar();
	return 0;
}

