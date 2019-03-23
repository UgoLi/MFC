
// ClientView.cpp : CClientView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Client.h"
#endif

#include "ClientDoc.h"
#include "ClientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClientView

IMPLEMENT_DYNCREATE(CClientView, CView)

BEGIN_MESSAGE_MAP(CClientView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_CONN, &CClientView::OnConn)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDBLCLK()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_APP_EXIT, &CClientView::OnAppExit)
END_MESSAGE_MAP()

// CClientView 构造/析构

CClientView::CClientView()
{
	// TODO: 在此处添加构造代码
	src=NULL;
	des=NULL;
	m_bStart=FALSE;
}

CClientView::~CClientView()
{
	if(m_bStart)
	{
		if(src)
			delete []src;
		if(des)
			delete []des;
		closesocket(m_hSockKM);
		closesocket(m_hSockScr);
	}
}

BOOL CClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CClientView 绘制

void CClientView::OnDraw(CDC* pDC)
{
	CClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if(!m_bStart)
		return;
	// TODO: 在此处为本机数据添加绘制代码
	CRect rect;
	GetClientRect(&rect);
	//	pDC=GetDC();
	HDC hdc=pDC->GetSafeHdc();

	StretchDIBits(hdc,
		// destination rectangle
		0, 0, rect.Width(), rect.Height(),
		// source rectangle
		0, 0, m_Screen.BmpCX, m_Screen.BmpCY,
		src+m_Screen.BmpInfoSize,
		(BITMAPINFO*)src,
		DIB_RGB_COLORS,
		SRCCOPY);


}


// CClientView 打印

BOOL CClientView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CClientView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CClientView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CClientView 诊断

#ifdef _DEBUG
void CClientView::AssertValid() const
{
	CView::AssertValid();
}

void CClientView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CClientDoc* CClientView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClientDoc)));
	return (CClientDoc*)m_pDocument;
}
#endif //_DEBUG


// CClientView 消息处理程序

UINT RecvScreenData(LPVOID pParam)
{
	CClientView* pView=(CClientView*)pParam;
	while(true)
	{
		if(pView->m_bStart)
		{
			pView->m_Screen.BmpSize=0;
		}
		else
		{
			pView->m_Screen.BmpSize=10000;
		}
		if(!pView->SendData(pView->m_hSockScr,(char*)&pView->m_Screen,sizeof(pView->m_Screen)))
		{
			continue;
		}
		if(!pView->RecvData(pView->m_hSockScr,(char*)&pView->m_Screen,sizeof(pView->m_Screen)))
		{
			continue;
		}
		if(!pView->RecvData(pView->m_hSockScr,(char*)pView->src,pView->m_Screen.BmpSize))
		{
			continue;
		}
		Sleep(100);
		pView->Invalidate();
	}
	return 0;
}

void CClientView::OnConn()
{
	m_bStart=TRUE;
	SOCKADDR_IN  addrSvr={0};
	addrSvr.sin_family=AF_INET;
	addrSvr.sin_port=htons(8111);
	addrSvr.sin_addr.S_un.S_addr=inet_addr("172.30.89.102");

	
	src=new char[4*1024*1024];
	m_hSockScr=socket(AF_INET,SOCK_STREAM,0);
	if(0!=connect(m_hSockScr,(SOCKADDR*)&addrSvr,sizeof(addrSvr)))
	{
		AfxMessageBox("连接服务器失败,检查服务器是否启动！");
		return;
	}
	m_CmdScr.CommandID=PEER_SCREEN_GET;
	SendData(m_hSockScr,(char*)&m_CmdScr,sizeof(m_CmdScr));
	AfxBeginThread(RecvScreenData, this);
	Sleep(100);
	
	m_hSockKM=socket(AF_INET,SOCK_STREAM,0);
	if(0!=connect(m_hSockKM,(SOCKADDR*)&addrSvr,sizeof(addrSvr)))
	{
		AfxMessageBox("连接服务器失败,检查服务器是否启动！！");
		return;
	}
	m_CmdKM.CommandID=PEER_KEYMOUSE;
	SendData(m_hSockKM,(char*)&m_CmdKM,sizeof(m_CmdKM));
	
	
}


BOOL CClientView::SendData(SOCKET  s,char* pData, long nLen)
{
	char* pTemp=pData;
	long nLeft=nLen;
	while(nLeft>0)
	{
		int nSend=send(s,pTemp,nLeft,0);
		if (nSend==SOCKET_ERROR)
		{
			return FALSE;
		}
		pTemp+=nSend;
		nLeft-=nSend;
	}
	return TRUE;
}


BOOL CClientView::RecvData(SOCKET s,char* pData, long nLen)
{
	char* pTemp=pData;
	long nLeft=nLen;
	while(nLeft>0)
	{
		int nRecv=recv(s,pTemp,nLeft,0);
		if (nRecv==SOCKET_ERROR)
		{
			return FALSE;
		}
		pTemp+=nRecv;
		nLeft-=nRecv;
	}
	return TRUE;
}


void CClientView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	KEYMOUSE keymouse;
	keymouse.style=PEER_KEY_DOWN;
	keymouse.nkey=nChar;
	SendData(m_hSockKM,(char*)&keymouse,sizeof(keymouse));
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CClientView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	KEYMOUSE keymouse;
	keymouse.style=PEER_KEY_UP;
	keymouse.nkey=nChar;
	SendData(m_hSockKM,(char*)&keymouse,sizeof(keymouse));
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CClientView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SendMouseData(PEER_MOUSE_LDBCLICK,point);

	CView::OnLButtonDblClk(nFlags, point);
}


void CClientView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SendMouseData(PEER_MOUSE_LEFTDOWN,point);
	CView::OnLButtonDown(nFlags, point);
}


void CClientView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SendMouseData(PEER_MOUSE_LEFTUP,point);

	CView::OnLButtonUp(nFlags, point);
}


void CClientView::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SendMouseData(PEER_MOUSE_MDBCLICK,point);
	CView::OnMButtonDblClk(nFlags, point);
}


void CClientView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SendMouseData(PEER_MOUSE_MIDDLEDOWN,point);
	CView::OnMButtonDown(nFlags, point);
}


void CClientView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SendMouseData(PEER_MOUSE_MIDDLEUP,point);
	CView::OnMButtonUp(nFlags, point);
}


void CClientView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SendMouseData(PEER_MOUSE_MOVE,point);
	CView::OnMouseMove(nFlags, point);
}


void CClientView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SendMouseData(PEER_MOUSE_RDBCLICK,point);
	CView::OnRButtonDblClk(nFlags, point);
}


void CClientView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SendMouseData(PEER_MOUSE_RIGHTDOWN,point);
	CView::OnRButtonDown(nFlags, point);
}


void CClientView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SendMouseData(PEER_MOUSE_RIGHTUP,point);
	CView::OnRButtonUp(nFlags, point);
}


void CClientView::SendMouseData(int nStyle,CPoint point)
{
	if(!m_bStart)
		return;
	KEYMOUSE keymouse;
	keymouse.style=nStyle;
	float fx,fy;
	CRect rect;
	GetClientRect(&rect);
	fx=(float)point.x/rect.Width();
	fy=(float)point.y/rect.Height();
	keymouse.x=65535*fx;
	keymouse.y=65535*fy;	
	SendData(m_hSockKM,(char*)&keymouse,sizeof(keymouse));
}





BOOL CClientView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_bStart)
		return false;
	else
		return CView::OnEraseBkgnd(pDC);
	
}


void CClientView::OnAppExit()
{
	// TODO: 在此添加命令处理程序代码
}
