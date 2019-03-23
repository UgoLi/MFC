
// MFCSdiView.h : CMFCSdiView ��Ľӿ�
//

#pragma once


class CMFCSdiView : public CEditView
{
protected: // �������л�����
	CMFCSdiView();
	DECLARE_DYNCREATE(CMFCSdiView)

// ����
public:
	CMFCSdiDoc* GetDocument() const;

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
	virtual ~CMFCSdiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MFCSdiView.cpp �еĵ��԰汾
inline CMFCSdiDoc* CMFCSdiView::GetDocument() const
   { return reinterpret_cast<CMFCSdiDoc*>(m_pDocument); }
#endif

