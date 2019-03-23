
// MFCSdiView.h : CMFCSdiView 类的接口
//

#pragma once


class CMFCSdiView : public CEditView
{
protected: // 仅从序列化创建
	CMFCSdiView();
	DECLARE_DYNCREATE(CMFCSdiView)

// 特性
public:
	CMFCSdiDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCSdiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MFCSdiView.cpp 中的调试版本
inline CMFCSdiDoc* CMFCSdiView::GetDocument() const
   { return reinterpret_cast<CMFCSdiDoc*>(m_pDocument); }
#endif

