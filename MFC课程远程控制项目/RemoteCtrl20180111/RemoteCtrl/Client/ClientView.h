
// ClientView.h : CClientView ��Ľӿ�
//

#pragma once


class CClientView : public CView
{
protected: // �������л�����
	CClientView();
	DECLARE_DYNCREATE(CClientView)
	SOCKET m_hSockScr;
	COMMAND m_CmdScr;
	SOCKET m_hSockKM;
	COMMAND m_CmdKM;
	SCREEN m_Screen;
	char *src,*des;
	BOOL m_bStart;
	
// ����
public:
	CClientDoc* GetDocument() const;

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
	virtual ~CClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnConn();
	BOOL SendData(SOCKET s,char* pData, long nLen);
	BOOL RecvData(SOCKET s,char* pData, long nLen);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	void SendMouseData(int nStyle,CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnAppExit();
};

#ifndef _DEBUG  // ClientView.cpp �еĵ��԰汾
inline CClientDoc* CClientView::GetDocument() const
   { return reinterpret_cast<CClientDoc*>(m_pDocument); }
#endif

