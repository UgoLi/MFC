
// MdiView.h : CMdiView ��Ľӿ�
//

#pragma once


class CMdiView : public CView
{
protected: // �������л�����
	CMdiView();
	DECLARE_DYNCREATE(CMdiView)

// ����
public:
	CMdiDoc* GetDocument() const;

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
	virtual ~CMdiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MdiView.cpp �еĵ��԰汾
inline CMdiDoc* CMdiView::GetDocument() const
   { return reinterpret_cast<CMdiDoc*>(m_pDocument); }
#endif

