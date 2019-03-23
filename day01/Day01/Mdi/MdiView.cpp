
// MdiView.cpp : CMdiView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMdiView ����/����

CMdiView::CMdiView()
{
	// TODO: �ڴ˴���ӹ������

}

CMdiView::~CMdiView()
{
}

BOOL CMdiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMdiView ����

void CMdiView::OnDraw(CDC* /*pDC*/)
{
	CMdiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMdiView ��ӡ

BOOL CMdiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMdiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMdiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMdiView ���

#ifdef _DEBUG
void CMdiView::AssertValid() const
{
	CView::AssertValid();
}

void CMdiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMdiDoc* CMdiView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMdiDoc)));
	return (CMdiDoc*)m_pDocument;
}
#endif //_DEBUG


// CMdiView ��Ϣ�������
