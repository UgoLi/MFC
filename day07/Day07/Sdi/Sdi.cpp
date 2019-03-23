#include <afxwin.h>
#include <afxext.h>
#include "resource.h"
// 4. 文档类 (支持动态创建)
class CMyDoc:public CDocument
{
DECLARE_DYNCREATE(CMyDoc)
};
IMPLEMENT_DYNCREATE(CMyDoc,CDocument)
// 3. 视图类 (支持动态创建)
class CMyView:public CEditView
{
DECLARE_DYNCREATE(CMyView)
};
IMPLEMENT_DYNCREATE(CMyView,CView)
// 2. 框架窗口类 (支持动态创建)
class CMyFrameWnd:public CFrameWnd
{
DECLARE_DYNCREATE(CMyFrameWnd)
};
IMPLEMENT_DYNCREATE(CMyFrameWnd,CFrameWnd)
// 1. 应用程序类
class CMyWinApp:public CWinApp
{
public:
	virtual BOOL InitInstance();
};
CMyWinApp theApp;
BOOL CMyWinApp::InitInstance()
{
	// 1. 创建单文档模板对象
	CSingleDocTemplate* pTemplate = new CSingleDocTemplate(
		IDR_MENU1,
		RUNTIME_CLASS(CMyDoc),
		RUNTIME_CLASS(CMyFrameWnd),
		RUNTIME_CLASS(CMyView));
	// 2. 将文档模板对象添加到应用程序
	AddDocTemplate(pTemplate);
	// 3. 新建文档
	OnFileNew();
/*
	int a = 20; // 假设 a 是其它函数传过来的数据
	ASSERT(a>10);  // 检查 a 是否符合条件，如果不符合，就报断言错误
*/
	return TRUE;
}