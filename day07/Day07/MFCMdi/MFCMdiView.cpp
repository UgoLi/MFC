
// MFCMdiView.cpp : CMFCMdiView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MFCMdi.h"
#endif

#include "MFCMdiDoc.h"
#include "MFCMdiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCMdiView

IMPLEMENT_DYNCREATE(CMFCMdiView, CView)

BEGIN_MESSAGE_MAP(CMFCMdiView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCMdiView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCMdiView ����/����

CMFCMdiView::CMFCMdiView()
{
	// TODO: �ڴ˴���ӹ������

}

CMFCMdiView::~CMFCMdiView()
{
}

BOOL CMFCMdiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMFCMdiView ����

void CMFCMdiView::OnDraw(CDC* /*pDC*/)
{
	CMFCMdiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMFCMdiView ��ӡ


void CMFCMdiView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCMdiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMFCMdiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMFCMdiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CMFCMdiView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCMdiView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCMdiView ���

#ifdef _DEBUG
void CMFCMdiView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCMdiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCMdiDoc* CMFCMdiView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCMdiDoc)));
	return (CMFCMdiDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCMdiView ��Ϣ�������
