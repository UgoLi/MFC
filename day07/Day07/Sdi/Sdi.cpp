#include <afxwin.h>
#include <afxext.h>
#include "resource.h"
// 4. �ĵ��� (֧�ֶ�̬����)
class CMyDoc:public CDocument
{
DECLARE_DYNCREATE(CMyDoc)
};
IMPLEMENT_DYNCREATE(CMyDoc,CDocument)
// 3. ��ͼ�� (֧�ֶ�̬����)
class CMyView:public CEditView
{
DECLARE_DYNCREATE(CMyView)
};
IMPLEMENT_DYNCREATE(CMyView,CView)
// 2. ��ܴ����� (֧�ֶ�̬����)
class CMyFrameWnd:public CFrameWnd
{
DECLARE_DYNCREATE(CMyFrameWnd)
};
IMPLEMENT_DYNCREATE(CMyFrameWnd,CFrameWnd)
// 1. Ӧ�ó�����
class CMyWinApp:public CWinApp
{
public:
	virtual BOOL InitInstance();
};
CMyWinApp theApp;
BOOL CMyWinApp::InitInstance()
{
	// 1. �������ĵ�ģ�����
	CSingleDocTemplate* pTemplate = new CSingleDocTemplate(
		IDR_MENU1,
		RUNTIME_CLASS(CMyDoc),
		RUNTIME_CLASS(CMyFrameWnd),
		RUNTIME_CLASS(CMyView));
	// 2. ���ĵ�ģ�������ӵ�Ӧ�ó���
	AddDocTemplate(pTemplate);
	// 3. �½��ĵ�
	OnFileNew();
/*
	int a = 20; // ���� a ����������������������
	ASSERT(a>10);  // ��� a �Ƿ������������������ϣ��ͱ����Դ���
*/
	return TRUE;
}