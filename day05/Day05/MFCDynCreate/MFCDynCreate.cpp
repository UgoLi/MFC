// MFCDynCreate.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <afxwin.h>
// 1. 创建对象的函数 (参数 RUNTIME_CLASS(类名))
CObject* CreateInstance(CRuntimeClass* pClass)
{
	return pClass->CreateObject();
}
// 2. 定义支持动态创建的类
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
	// 3. 使用
	CObject* pObj = CreateInstance(RUNTIME_CLASS(CDog));
	if(pObj)
	{
		printf("对象地址：%p\n",pObj);
		printf("类的名称:%s\n",pObj->GetRuntimeClass()->m_lpszClassName);
	}
	delete pObj;
	pObj = NULL;
	getchar();
	return 0;
}

