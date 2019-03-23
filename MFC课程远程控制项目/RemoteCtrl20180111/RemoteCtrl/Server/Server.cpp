#include <stdio.h>
#include <WinSock2.h>
#pragma  comment(lib,"ws2_32.lib")

#include "command.h"

// λͼ�ߴ�
int	  iBmpCX;
int   iBmpCY;
//  λͼ����ָ��
LPSTR lpBmpData=NULL;
//  λͼ��С
DWORD dwBmpSize=0;
// λͼ��Ϣ��С
DWORD dwBmpInfoSize=0;


// 1 ��������
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
// 2 ��������
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
// 3 �ӿͻ��˽������������ݲ�����
BOOL GetMouseKeyData(SOCKET& s)
{
	KEYMOUSE keymouse;
	while(1)
	{
		//////////ȡ��������ֵ///////////
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

// 4 ץȡ����������Ļ����
bool CaptureScreen(int nBits)
{
	//λͼλ������Ϊ����2^24��ֵ,��Ҫ���ǵ���������
	if (nBits>24)
		return false;

	HDC		hScrDC, hMemDC;			// ��Ļ���ڴ��豸������
	
	HDC		hDC;				//�豸������
	WORD		wBitCount;			//λͼ��ÿ��������ռ�ֽ���

	//�����ɫ���С�� λͼ�������ֽڴ�С ��λͼ�ļ���С �� д���ļ��ֽ���
	DWORD		dwPaletteSize=0, dwBmBitsSize=0;//,dwBmpInfoSize=0;
	BITMAP		Bitmap;			//λͼ���Խṹ
	BITMAPINFOHEADER	bi;		//λͼ��Ϣͷ�ṹ 
	LPBITMAPINFOHEADER	lpbi;		//ָ��λͼ��Ϣͷ�ṹ

	//�����ļ��������ڴ�������ɫ����  
	HANDLE			hDib;
	HPALETTE		hPal,hOldPal=NULL;

	//Ϊ��Ļ�����豸������
	hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	// �����Ļ�ֱ���
	int xScrn = GetDeviceCaps(hScrDC, HORZRES);
	int yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
	hMemDC = CreateCompatibleDC(hScrDC);
	// ����һ������Ļ�豸��������ݵ�λͼ
	HBITMAP hBitmap = CreateCompatibleBitmap (hScrDC,xScrn,yScrn);
	// ����λͼѡ���ڴ��豸��������
	HBITMAP hOldBitmap = (HBITMAP) SelectObject(hMemDC, hBitmap);
	// ����Ļ�豸�����������ڴ��豸��������
	BitBlt(hMemDC, 0, 0, xScrn, yScrn, 
			hScrDC, 0, 0, SRCCOPY);
	//�õ���Ļλͼ�ľ��
	hBitmap = (HBITMAP) SelectObject(hMemDC, hOldBitmap);


	//����λͼÿ��������ռ�ֽ���
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

	//�����ɫ���С
	if (wBitCount <24)
		dwPaletteSize = (1 << wBitCount) * sizeof(RGBQUAD);

	//����λͼ�������ȡλͼ��������Ϣ�����ô���ʱ��λͼ��Ϣͷ�ṹ
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
	/*xxxxxxxx����λͼ��С�ֽ�һ��(����һ����������)xxxxxxxxxxxxxxxxxxxx 
//ÿ��ɨ������ռ���ֽ���Ӧ��Ϊ4���������������㷨Ϊ:
 int biWidth = (Bitmap.bmWidth*wBitCount) / 32;
 if((Bitmap.bmWidth*wBitCount) % 32)
  biWidth++; //�����������ļ�1
 biWidth *= 4;//���������õ���Ϊÿ��ɨ���е��ֽ�����
 dwBmBitsSize = biWidth * Bitmap.bmHeight;//�õ���С
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
	 dwBmBitsSize = ((Bitmap.bmWidth * wBitCount+31)& ~31)/8 *Bitmap.bmHeight;
	dwBmpInfoSize = dwPaletteSize + sizeof(BITMAPINFOHEADER);
	//��ʱλͼ���ݴ�С����
	DWORD dwNewBmpSize;
	dwNewBmpSize = dwBmBitsSize + dwBmpInfoSize;
	iBmpCX=Bitmap.bmWidth;
	iBmpCY=Bitmap.bmHeight;
	//Ϊλͼ���ݷ����ڴ�
	if(dwNewBmpSize!=dwBmpSize)//λͼ�����Ϣû�б仯
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
	else//λͼ�����Ϣû�б仯
	{
		lpbi = (LPBITMAPINFOHEADER)lpBmpData;
		*lpbi = bi;
	}

	// �����ɫ��   
	hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = GetDC (NULL);
		hOldPal = SelectPalette(hDC, hPal, FALSE);
		RealizePalette(hDC);
	}
	// ��ȡ�õ�ɫ�����µ�����ֵ
	GetDIBits(
			hDC,
			hBitmap,
			0, 
			(UINT) Bitmap.bmHeight,
			(LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize,
			(BITMAPINFO *)lpbi,
			DIB_RGB_COLORS
		  );
	//�ָ���ɫ��
	if (hOldPal)
	{
		SelectPalette(hScrDC, hOldPal, TRUE);
		RealizePalette(hScrDC);
		ReleaseDC(NULL, hDC);
	}

	lpBmpData = (char *)lpbi;
	dwBmpSize = dwNewBmpSize;
	//���
	DeleteObject (hBitmap);
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	return TRUE;

}

// 5 ��ͻ��˷�����Ļ����
BOOL SendScreenData(SOCKET s)
{
	SCREEN screen;
	//////////��Ļ///////////
	while(1)
	{
		// 1 ���տͻ��˵�����
		if(!RecvData(s,(char*)&screen,sizeof(screen)))
		{
			return FALSE;
		}
		if(screen.BmpSize==10000) ///�ͻ����Ѿ��˳�
			break;
	    // 2 ץȡ��������Ļ����
		if(!CaptureScreen(24))
		{
			return false;
		}
		screen.BmpSize=dwBmpSize;
		screen.BmpInfoSize=dwBmpInfoSize;
		screen.BmpCX=iBmpCX;
		screen.BmpCY=iBmpCY;
		// 3 ��ͻ��˷�����Ļ��Ϣ
		if(!SendData(s,(char*)&screen,sizeof(screen)))
		{
			return FALSE;
		}
		// 4 ��ͻ��˷�����Ļ����
		if(!SendData(s,(char*)lpBmpData,dwBmpSize))
		{
			return FALSE;
		}
	}
	return TRUE;
}
//����ɨβ����,�ͷ��ڴ棬�ڷ����̺߳���ServerThread��ʹ��
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
		//���������Ƚ�������
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
		//���߳���,�ֱ�����Ļ���ݺͼ����������
		DWORD nID=0;
		CreateThread(NULL,0,CommProc,(LPVOID)hSockClient,0,&nID);
	}
	getchar();
	closesocket(hSockSvr);
	return 0;
}

int main()
{
	// 1 ��ʼ��socket��
	WSADATA wd={0};
	WSAStartup(MAKEWORD(2,2),&wd);

	// 2 TCPͨ��
	DWORD nID=0;
	HANDLE hThread= CreateThread(NULL,1,TCPServer,NULL,0,&nID);
	CloseHandle (hThread);
	TCPServer(NULL);

	// 3 ж��socket��
	WSACleanup();
	return 0;
}