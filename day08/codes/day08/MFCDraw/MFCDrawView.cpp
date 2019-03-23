
// MFCDrawView.cpp : CMFCDrawView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MFCDraw.h"
#endif

#include "MFCDrawDoc.h"
#include "MFCDrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCDrawView

IMPLEMENT_DYNCREATE(CMFCDrawView, CView)

BEGIN_MESSAGE_MAP(CMFCDrawView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCDrawView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DC, &CMFCDrawView::OnDc)
	ON_COMMAND(ID_DC_CLIENT, &CMFCDrawView::OnDcClient)
	ON_WM_PAINT()
	ON_COMMAND(ID_GDI_PEN, &CMFCDrawView::OnGdiPen)
	ON_COMMAND(ID_GDI_BRUSH, &CMFCDrawView::OnGdiBrush)
	ON_COMMAND(ID_GDI_FONT, &CMFCDrawView::OnGdiFont)
	ON_COMMAND(ID_GDI_BMP, &CMFCDrawView::OnGdiBmp)
	ON_COMMAND(ID_GDI_RGN, &CMFCDrawView::OnGdiRgn)
END_MESSAGE_MAP()

// CMFCDrawView ����/����

CMFCDrawView::CMFCDrawView()
{
	// TODO: �ڴ˴���ӹ������

}

CMFCDrawView::~CMFCDrawView()
{
}

BOOL CMFCDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMFCDrawView ����

void CMFCDrawView::OnDraw(CDC* /*pDC*/)
{
	CMFCDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMFCDrawView ��ӡ


void CMFCDrawView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMFCDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMFCDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CMFCDrawView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCDrawView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCDrawView ���

#ifdef _DEBUG
void CMFCDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDrawDoc* CMFCDrawView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDrawDoc)));
	return (CMFCDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCDrawView ��Ϣ�������


void CMFCDrawView::OnDc()
{
	// CDC��ʹ��
	CDC dc;
	// 1 ����DC
	dc.CreateDC("DISPLAY",NULL,NULL,NULL);
	// 2 ʹ��DC(��DC�ϻ�ͼ)
	dc.TextOut(0,0,"Hello CDC");
	dc.MoveTo(0,0);
	dc.LineTo(1024,768);
	dc.Rectangle(300,300,500,500);
	// 3 ɾ��DC
	dc.DeleteDC();


}


void CMFCDrawView::OnDcClient()
{
	// CClientDC��ʹ��
	CClientDC dc(this);
	dc.TextOut(0,0,"Hello CClientDC");

}


void CMFCDrawView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.TextOut(0,100,"Hello CPaintDC");
}


void CMFCDrawView::OnGdiPen()
{
	// 1 ����
	CPen pen(PS_SOLID,5,RGB(255,0,0));
	CClientDC dc(this);
	CPen *pOldPen=dc.SelectObject(&pen);
	dc.Rectangle(100,100,300,300);
	dc.SelectObject(pOldPen);
	pen.DeleteObject();

}


void CMFCDrawView::OnGdiBrush()
{
	// 2 ��ˢ����ɫ����Ӱ��λͼ��ˢ��
	//CBrush brush(HS_CROSS ,RGB(255,255,0));
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP1);
	CBrush brush(&bmp);
	CClientDC dc(this);
	CBrush* pOldBrush=dc.SelectObject(&brush);
	dc.Rectangle(100,100,500,500);
	dc.SelectObject(pOldBrush);
	brush.DeleteObject();

}


void CMFCDrawView::OnGdiFont()
{
	// 3 ����(CFont font;font.CreatePointFont)
	CFont font;
	font.CreatePointFont(1000,"����");
	CClientDC dc(this);
	CFont * pOldFont=dc.SelectObject(&font);
	dc.TextOut(100,100,"Hello,����Ϊ����");
	dc.SelectObject(pOldFont);
	font.DeleteObject();

}


void CMFCDrawView::OnGdiBmp()
{
	// 4 λͼ
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP2);
	CClientDC dc(this);
	CDC dcBmp;
	dcBmp.CreateCompatibleDC(&dc);
	dcBmp.SelectObject(&bmp);
	//dc.BitBlt(0,0,559,436,&dcBmp,0,0,SRCCOPY);
	// 1 ��ȡ��ͼ���ڵĿͻ�����С
	CRect rt;
	GetClientRect(rt);
	// 2 dc.StretchBlt()
	dc.StretchBlt(0,0,rt.Width(),rt.Height(),&dcBmp,
		0,0,559,436,SRCCOPY);
	dcBmp.DeleteDC();
	bmp.DeleteObject();
}


void CMFCDrawView::OnGdiRgn()
{
	// 5 ����
	// 1 ��������
	CRgn rgn1,rgn2;
	rgn1.CreateEllipticRgn(100,100,300,300);
	rgn2.CreateEllipticRgn(200,100,400,300);
	// 2 ��������(���Զ��)
	rgn1.CombineRgn(&rgn1,&rgn2,RGN_AND);
	// 3 �������
	CBrush brush(RGB(0,0,255));
	CClientDC dc(this);
	dc.FillRgn(&rgn1,&brush);
}
