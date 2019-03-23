
// ClientView.cpp : CClientView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CClientView ����/����

CClientView::CClientView()
{
	// TODO: �ڴ˴���ӹ������
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CClientView ����

void CClientView::OnDraw(CDC* pDC)
{
	CClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if(!m_bStart)
		return;
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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


// CClientView ��ӡ

BOOL CClientView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CClientView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CClientView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CClientView ���

#ifdef _DEBUG
void CClientView::AssertValid() const
{
	CView::AssertValid();
}

void CClientView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CClientDoc* CClientView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClientDoc)));
	return (CClientDoc*)m_pDocument;
}
#endif //_DEBUG


// CClientView ��Ϣ�������

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
		AfxMessageBox("���ӷ�����ʧ��,���������Ƿ�������");
		return;
	}
	m_CmdScr.CommandID=PEER_SCREEN_GET;
	SendData(m_hSockScr,(char*)&m_CmdScr,sizeof(m_CmdScr));
	AfxBeginThread(RecvScreenData, this);
	Sleep(100);
	
	m_hSockKM=socket(AF_INET,SOCK_STREAM,0);
	if(0!=connect(m_hSockKM,(SOCKADDR*)&addrSvr,sizeof(addrSvr)))
	{
		AfxMessageBox("���ӷ�����ʧ��,���������Ƿ���������");
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	KEYMOUSE keymouse;
	keymouse.style=PEER_KEY_DOWN;
	keymouse.nkey=nChar;
	SendData(m_hSockKM,(char*)&keymouse,sizeof(keymouse));
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CClientView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	KEYMOUSE keymouse;
	keymouse.style=PEER_KEY_UP;
	keymouse.nkey=nChar;
	SendData(m_hSockKM,(char*)&keymouse,sizeof(keymouse));
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CClientView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMouseData(PEER_MOUSE_LDBCLICK,point);

	CView::OnLButtonDblClk(nFlags, point);
}


void CClientView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMouseData(PEER_MOUSE_LEFTDOWN,point);
	CView::OnLButtonDown(nFlags, point);
}


void CClientView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMouseData(PEER_MOUSE_LEFTUP,point);

	CView::OnLButtonUp(nFlags, point);
}


void CClientView::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMouseData(PEER_MOUSE_MDBCLICK,point);
	CView::OnMButtonDblClk(nFlags, point);
}


void CClientView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMouseData(PEER_MOUSE_MIDDLEDOWN,point);
	CView::OnMButtonDown(nFlags, point);
}


void CClientView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMouseData(PEER_MOUSE_MIDDLEUP,point);
	CView::OnMButtonUp(nFlags, point);
}


void CClientView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMouseData(PEER_MOUSE_MOVE,point);
	CView::OnMouseMove(nFlags, point);
}


void CClientView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMouseData(PEER_MOUSE_RDBCLICK,point);
	CView::OnRButtonDblClk(nFlags, point);
}


void CClientView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMouseData(PEER_MOUSE_RIGHTDOWN,point);
	CView::OnRButtonDown(nFlags, point);
}


void CClientView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_bStart)
		return false;
	else
		return CView::OnEraseBkgnd(pDC);
	
}


void CClientView::OnAppExit()
{
	// TODO: �ڴ���������������
}
