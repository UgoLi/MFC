
// MyNotePadView.h : CMyNotePadView ��Ľӿ�
//

#pragma once


class CMyNotePadView : public CEditView
{
protected: // �������л�����
	CMyNotePadView();
	DECLARE_DYNCREATE(CMyNotePadView)

// ����
public:
	CMyNotePadDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMyNotePadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MyNotePadView.cpp �еĵ��԰汾
inline CMyNotePadDoc* CMyNotePadView::GetDocument() const
   { return reinterpret_cast<CMyNotePadDoc*>(m_pDocument); }
#endif

