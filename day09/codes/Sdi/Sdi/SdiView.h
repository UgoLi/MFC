
// SdiView.h : CSdiView ��Ľӿ�
//

#pragma once


class CSdiView : public CView
{
protected: // �������л�����
	CSdiView();
	DECLARE_DYNCREATE(CSdiView)

// ����
public:
	CSdiDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CSdiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // SdiView.cpp �еĵ��԰汾
inline CSdiDoc* CSdiView::GetDocument() const
   { return reinterpret_cast<CSdiDoc*>(m_pDocument); }
#endif

