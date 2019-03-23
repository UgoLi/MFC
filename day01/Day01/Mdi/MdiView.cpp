
// MdiView.cpp : CMdiView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Mdi.h"
#endif

#include "MdiDoc.h"
#include "MdiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMdiView

IMPLEMENT_DYNCREATE(CMdiView, CView)

BEGIN_MESSAGE_MAP(CMdiView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMdiView 构造/析构

CMdiView::CMdiView()
{
	// TODO: 在此处添加构造代码

}

CMdiView::~CMdiView()
{
}

BOOL CMdiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMdiView 绘制

void CMdiView::OnDraw(CDC* /*pDC*/)
{
	CMdiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMdiView 打印

BOOL CMdiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMdiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMdiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMdiView 诊断

#ifdef _DEBUG
void CMdiView::AssertValid() const
{
	CView::AssertValid();
}

void CMdiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMdiDoc* CMdiView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMdiDoc)));
	return (CMdiDoc*)m_pDocument;
}
#endif //_DEBUG


// CMdiView 消息处理程序
