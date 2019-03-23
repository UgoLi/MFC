
// SdiView.cpp : CSdiView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Sdi.h"
#endif

#include "SdiDoc.h"
#include "SdiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSdiView

IMPLEMENT_DYNCREATE(CSdiView, CView)

BEGIN_MESSAGE_MAP(CSdiView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CSdiView ����/����

CSdiView::CSdiView()
{
	// TODO: �ڴ˴���ӹ������

}

CSdiView::~CSdiView()
{
}

BOOL CSdiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CSdiView ����

void CSdiView::OnDraw(CDC* /*pDC*/)
{
	CSdiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CSdiView ��ӡ

BOOL CSdiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CSdiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CSdiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CSdiView ���

#ifdef _DEBUG
void CSdiView::AssertValid() const
{
	CView::AssertValid();
}

void CSdiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSdiDoc* CSdiView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSdiDoc)));
	return (CSdiDoc*)m_pDocument;
}
#endif //_DEBUG


// CSdiView ��Ϣ�������
