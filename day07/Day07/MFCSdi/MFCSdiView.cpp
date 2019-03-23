
// MFCSdiView.cpp : CMFCSdiView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MFCSdi.h"
#endif

#include "MFCSdiDoc.h"
#include "MFCSdiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCSdiView

IMPLEMENT_DYNCREATE(CMFCSdiView, CEditView)

BEGIN_MESSAGE_MAP(CMFCSdiView, CEditView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCSdiView ����/����

CMFCSdiView::CMFCSdiView()
{
	// TODO: �ڴ˴���ӹ������

}

CMFCSdiView::~CMFCSdiView()
{
}

BOOL CMFCSdiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// ���û���

	return bPreCreated;
}


// CMFCSdiView ��ӡ

BOOL CMFCSdiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ׼��
	return CEditView::OnPreparePrinting(pInfo);
}

void CMFCSdiView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ��ʼ��ӡ
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CMFCSdiView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ������ӡ
	CEditView::OnEndPrinting(pDC, pInfo);
}


// CMFCSdiView ���

#ifdef _DEBUG
void CMFCSdiView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMFCSdiView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMFCSdiDoc* CMFCSdiView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCSdiDoc)));
	return (CMFCSdiDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCSdiView ��Ϣ�������
