#include <stdio.h>
#include <WinSock2.h>
#pragma  comment(lib,"ws2_32.lib")

#include "command.h"

// 位图尺寸
int	  iBmpCX;
int   iBmpCY;
//  位图数据指针
LPSTR lpBmpData=NULL;
//  位图大小
DWORD dwBmpSize=0;
// 位图信息大小
DWORD dwBmpInfoSize=0;


// 1 接收数据
BOOL RecvData( SOCKET & hSockClient,char* pData,long nLen)
{
	char* pTemp=pData;
	long nLeft=nLen;
	while(nLeft>0)
	{
		int nRecv=recv(hSockClient,pTemp,nLeft,0);
		if (nRecv==SOCKET_ERROR)
		{
			return FALSE;
		}
		pTemp+=nRecv;
		nLeft-=nRecv;
	}
	return TRUE;
}
// 2 发送数据
BOOL SendData( SOCKET&  hSockClient,char* pData,long nLen )
{
	char* pTemp=pData;
	long nLeft=nLen;
	while(nLeft>0)
	{
		int nSend=send(hSockClient,pTemp,nLeft,0);
		if (nSend==SOCKET_ERROR)
		{
			return FALSE;
		}
		pTemp+=nSend;
		nLeft-=nSend;
	}
	return TRUE;
}
// 3 从客户端接收鼠标键盘数据并处理
BOOL GetMouseKeyData(SOCKET& s)
{
	KEYMOUSE keymouse;
	while(1)
	{
		//////////取得鼠标键盘值///////////
		if(!RecvData(s,(char*)&keymouse,sizeof(keymouse)))
		{
			return FALSE;
		}
		switch(keymouse.style)
		{
		case PEER_MOUSE_LEFTDOWN:
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN,keymouse.x,keymouse.y,0,0);
			break;
		case PEER_MOUSE_LEFTUP:
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP,keymouse.x,keymouse.y,0,0);
			break;
		case PEER_MOUSE_RIGHTDOWN:
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN,keymouse.x,keymouse.y,0,0);
			break;
		case PEER_MOUSE_RIGHTUP:
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP,keymouse.x,keymouse.y,0,0);
			break;
		case PEER_MOUSE_MIDDLEDOWN:
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEDOWN,keymouse.x,keymouse.y,0,0);
			break;
		case PEER_MOUSE_MIDDLEUP:
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEUP,keymouse.x,keymouse.y,0,0);
			break;
		case PEER_MOUSE_LDBCLICK:
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN,keymouse.x,keymouse.y,0,0);
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP,keymouse.x,keymouse.y,0,0);
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN,keymouse.x,keymouse.y,0,0);
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP,keymouse.x,keymouse.y,0,0);
			break;
		case PEER_MOUSE_RDBCLICK:
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN,keymouse.x,keymouse.y,0,0);
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP,keymouse.x,keymouse.y,0,0);
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN,keymouse.x,keymouse.y,0,0);
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP,keymouse.x,keymouse.y,0,0);
			break;
		case PEER_MOUSE_MDBCLICK:
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEDOWN,keymouse.x,keymouse.y,0,0);
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEUP,keymouse.x,keymouse.y,0,0);
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEDOWN,keymouse.x,keymouse.y,0,0);
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEUP,keymouse.x,keymouse.y,0,0);
			break;
		case PEER_MOUSE_MOVE:
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE,keymouse.x,keymouse.y,0,0);
			break;
		case PEER_KEY_DOWN:
			keybd_event(keymouse.nkey,0,KEYEVENTF_EXTENDEDKEY,0);
			break;
		case PEER_KEY_UP:
			keybd_event(keymouse.nkey,0,KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP,0);
			break;
		default:
			break;
		}
	}
	return TRUE;
}

// 4 抓取服务器的屏幕数据
bool CaptureScreen(int nBits)
{
	//位图位数不能为大于2^24的值,主要考虑到传输特性
	if (nBits>24)
		return false;

	HDC		hScrDC, hMemDC;			// 屏幕和内存设备描述表
	
	HDC		hDC;				//设备描述表
	WORD		wBitCount;			//位图中每个像素所占字节数

	//定义调色板大小， 位图中像素字节大小 ，位图文件大小 ， 写入文件字节数
	DWORD		dwPaletteSize=0, dwBmBitsSize=0;//,dwBmpInfoSize=0;
	BITMAP		Bitmap;			//位图属性结构
	BITMAPINFOHEADER	bi;		//位图信息头结构 
	LPBITMAPINFOHEADER	lpbi;		//指向位图信息头结构

	//定义文件，分配内存句柄，调色板句柄  
	HANDLE			hDib;
	HPALETTE		hPal,hOldPal=NULL;

	//为屏幕创建设备描述表
	hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	// 获得屏幕分辨率
	int xScrn = GetDeviceCaps(hScrDC, HORZRES);
	int yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//为屏幕设备描述表创建兼容的内存设备描述表
	hMemDC = CreateCompatibleDC(hScrDC);
	// 创建一个与屏幕设备描述表兼容的位图
	HBITMAP hBitmap = CreateCompatibleBitmap (hScrDC,xScrn,yScrn);
	// 把新位图选到内存设备描述表中
	HBITMAP hOldBitmap = (HBITMAP) SelectObject(hMemDC, hBitmap);
	// 把屏幕设备描述表拷贝到内存设备描述表中
	BitBlt(hMemDC, 0, 0, xScrn, yScrn, 
			hScrDC, 0, 0, SRCCOPY);
	//得到屏幕位图的句柄
	hBitmap = (HBITMAP) SelectObject(hMemDC, hOldBitmap);


	//计算位图每个像素所占字节数
	if (nBits <= 1)
		wBitCount = 1;
	else if (nBits <= 4)
		wBitCount = 4;
	else if (nBits <= 8)
		wBitCount = 8;
	else if (nBits <= 16)
		wBitCount = 16;
	else if (nBits <= 24)
		wBitCount = 24;

	//计算调色板大小
	if (wBitCount <24)
		dwPaletteSize = (1 << wBitCount) * sizeof(RGBQUAD);

	//根据位图句柄，获取位图的属性信息，设置传输时的位图信息头结构
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap.bmWidth;
	bi.biHeight = Bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	//dwBmBitsSize = ((Bitmap.bmWidth*wBitCount+31)/32)*4*Bitmap.bmHeight; 
	/*xxxxxxxx计算位图大小分解一下(解释一下上面的语句)xxxxxxxxxxxxxxxxxxxx 
//每个扫描行所占的字节数应该为4的整数倍，具体算法为:
 int biWidth = (Bitmap.bmWidth*wBitCount) / 32;
 if((Bitmap.bmWidth*wBitCount) % 32)
  biWidth++; //不是整数倍的加1
 biWidth *= 4;//到这里，计算得到的为每个扫描行的字节数。
 dwBmBitsSize = biWidth * Bitmap.bmHeight;//得到大小
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
	 dwBmBitsSize = ((Bitmap.bmWidth * wBitCount+31)& ~31)/8 *Bitmap.bmHeight;
	dwBmpInfoSize = dwPaletteSize + sizeof(BITMAPINFOHEADER);
	//临时位图数据大小变量
	DWORD dwNewBmpSize;
	dwNewBmpSize = dwBmBitsSize + dwBmpInfoSize;
	iBmpCX=Bitmap.bmWidth;
	iBmpCY=Bitmap.bmHeight;
	//为位图内容分配内存
	if(dwNewBmpSize!=dwBmpSize)//位图相关信息没有变化
	{
		if(!lpBmpData)
		{
			hDib  = GlobalAlloc(GHND,dwNewBmpSize);
			if(!hDib)
			{
				DeleteObject(hBitmap);
				DeleteDC(hScrDC);
				DeleteDC(hMemDC);
				dwBmpSize=0;
				dwBmpInfoSize=0;
				return false;
			}
		}
		else
		{
			GlobalUnlock(lpBmpData);
			lpBmpData=(char*)GlobalFree(lpBmpData);
			hDib  = GlobalAlloc(GHND,dwNewBmpSize);
			if(!hDib)
			{
				DeleteObject(hBitmap);
				DeleteDC(hScrDC);
				DeleteDC(hMemDC);
				dwBmpSize=0;
				dwBmpInfoSize=0;
				return false;
			}
		}
		lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
		*lpbi = bi;
	}
	else//位图相关信息没有变化
	{
		lpbi = (LPBITMAPINFOHEADER)lpBmpData;
		*lpbi = bi;
	}

	// 处理调色板   
	hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = GetDC (NULL);
		hOldPal = SelectPalette(hDC, hPal, FALSE);
		RealizePalette(hDC);
	}
	// 获取该调色板下新的像素值
	GetDIBits(
			hDC,
			hBitmap,
			0, 
			(UINT) Bitmap.bmHeight,
			(LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize,
			(BITMAPINFO *)lpbi,
			DIB_RGB_COLORS
		  );
	//恢复调色板
	if (hOldPal)
	{
		SelectPalette(hScrDC, hOldPal, TRUE);
		RealizePalette(hScrDC);
		ReleaseDC(NULL, hDC);
	}

	lpBmpData = (char *)lpbi;
	dwBmpSize = dwNewBmpSize;
	//清除
	DeleteObject (hBitmap);
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	return TRUE;

}

// 5 向客户端发送屏幕数据
BOOL SendScreenData(SOCKET s)
{
	SCREEN screen;
	//////////屏幕///////////
	while(1)
	{
		// 1 接收客户端的命令
		if(!RecvData(s,(char*)&screen,sizeof(screen)))
		{
			return FALSE;
		}
		if(screen.BmpSize==10000) ///客户端已经退出
			break;
	    // 2 抓取服务器屏幕数据
		if(!CaptureScreen(24))
		{
			return false;
		}
		screen.BmpSize=dwBmpSize;
		screen.BmpInfoSize=dwBmpInfoSize;
		screen.BmpCX=iBmpCX;
		screen.BmpCY=iBmpCY;
		// 3 向客户端发送屏幕信息
		if(!SendData(s,(char*)&screen,sizeof(screen)))
		{
			return FALSE;
		}
		// 4 向客户端发送屏幕数据
		if(!SendData(s,(char*)lpBmpData,dwBmpSize))
		{
			return FALSE;
		}
	}
	return TRUE;
}
//进行扫尾工作,释放内存，在服务线程函数ServerThread中使用
void CleanScreenData(void)
{
	if(lpBmpData)
	{
		GlobalUnlock(lpBmpData);
		lpBmpData=(char*)GlobalFree(lpBmpData);
	}
	dwBmpSize=0;
	dwBmpInfoSize=0;
}
DWORD WINAPI CommProc (LPVOID pParam)
{
	SOCKET hSockClient=(SOCKET)pParam;
	while(1)
	{
		//服务器首先接收数据
		COMMAND cmd;
		BOOL bRet=RecvData(hSockClient,(char*)&cmd,sizeof(cmd));
		if (!bRet)
		{
			continue;
		}
		switch(cmd.CommandID)
		{
		case PEER_KEYMOUSE:
			GetMouseKeyData(hSockClient);
			break;
		case PEER_SCREEN_GET:
			SendScreenData(hSockClient);
			CleanScreenData();
			break;
		}
	}
	return 0;
}

DWORD WINAPI TCPServer(LPVOID pParam)
{
	SOCKET  hSockSvr=socket(AF_INET,SOCK_STREAM,0);
	SOCKADDR_IN  addrSvr={0};
	addrSvr.sin_family=AF_INET;
	addrSvr.sin_port=htons(8111);
	addrSvr.sin_addr.S_un.S_addr=INADDR_ANY;
	bind(hSockSvr,(SOCKADDR*)&addrSvr,sizeof(addrSvr));
	listen(hSockSvr,10);
	SOCKADDR_IN addrClient={0};
	int nLen=sizeof(addrClient);
	for(int i=0;i<2;i++)
	{
		SOCKET hSockClient=accept(hSockSvr,(SOCKADDR*)&addrClient,&nLen);
		//在线程中,分别处理屏幕数据和键盘鼠标数据
		DWORD nID=0;
		CreateThread(NULL,0,CommProc,(LPVOID)hSockClient,0,&nID);
	}
	getchar();
	closesocket(hSockSvr);
	return 0;
}

int main()
{
	// 1 初始化socket库
	WSADATA wd={0};
	WSAStartup(MAKEWORD(2,2),&wd);

	// 2 TCP通信
	DWORD nID=0;
	HANDLE hThread= CreateThread(NULL,1,TCPServer,NULL,0,&nID);
	CloseHandle (hThread);
	TCPServer(NULL);

	// 3 卸载socket库
	WSACleanup();
	return 0;
}