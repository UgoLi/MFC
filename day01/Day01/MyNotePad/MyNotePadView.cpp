
// MyNotePadView.cpp : CMyNotePadView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MyNotePad.h"
#endif

#include "MyNotePadDoc.h"
#include "MyNotePadView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyNotePadView

IMPLEMENT_DYNCREATE(CMyNotePadView, CEditView)

BEGIN_MESSAGE_MAP(CMyNotePadView, CEditView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMyNotePadView ����/����

CMyNotePadView::CMyNotePadView()
{
	// TODO: �ڴ˴���ӹ������

}

CMyNotePadView::~CMyNotePadView()
{
}

BOOL CMyNotePadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// ���û���

	return bPreCreated;
}


// CMyNotePadView ��ӡ

BOOL CMyNotePadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ׼��
	return CEditView::OnPreparePrinting(pInfo);
}

void CMyNotePadView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ��ʼ��ӡ
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CMyNotePadView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ������ӡ
	CEditView::OnEndPrinting(pDC, pInfo);
}


// CMyNotePadView ���

#ifdef _DEBUG
void CMyNotePadView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMyNotePadView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMyNotePadDoc* CMyNotePadView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyNotePadDoc)));
	return (CMyNotePadDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyNotePadView ��Ϣ�������
