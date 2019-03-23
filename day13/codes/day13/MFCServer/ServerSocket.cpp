// ServerSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCServer.h"
#include "ServerSocket.h"


// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// CServerSocket 成员函数

BOOL CServerSocket::InitServer(UINT nPort)
{
	if (!Create(nPort))//创建和绑定
	{
		return FALSE;
	}
	return Listen();//监听
}
typedef struct _tagHeader
{
   char szName[256];
   long nLen;
}HEADER,*LPHEADER;
BOOL CServerSocket::RecvData(CSocket& client,BYTE* pData,long nLen)
{
	BYTE* pTmpData=pData;
	long nLeft=nLen;//剩余的还没有接收的数据的长度
	while (nLeft>0)
	{
		int nRecv=client.Receive(pTmpData,nLeft);
		if (nRecv==SOCKET_ERROR)
		{
			return FALSE;
		}
		nLeft=nLeft-nRecv;
		pTmpData=pTmpData+nRecv;
	}
	return TRUE;
}
void CServerSocket::OnAccept(int nErrorCode)
{
	// 接收连接
	CSocket client;
	Accept(client);
	// 通信(接收文件)
	// 1 首先接收文件信息(文件名称和长度)
	HEADER header={0};
	if (!RecvData(client,(BYTE*)&header,sizeof(header)))
	{
		AfxMessageBox("发送文件信息失败！");
		return;
	}
	// 2 然后接收文件数据
	BYTE* pData=(BYTE*)malloc(header.nLen);
	if (!RecvData(client,pData,header.nLen))
	{
		AfxMessageBox("发送文件数据失败！");
		return;
	}
	// 3 将文件保存到服务器(写文件操作)
	CFile file;
	CString strPath="d:/";
	strPath+=header.szName;
	file.Open(strPath,CFile::modeCreate|CFile::modeWrite);
	file.Write(pData,header.nLen);
	file.Close();
	free(pData);
	// 关闭
	client.Close();
	CAsyncSocket::OnAccept(nErrorCode);
}
