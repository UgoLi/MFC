// ClientSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCClient.h"
#include "ClientSocket.h"


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 成员函数
// 1 初始化客户端(创建、连接)
BOOL CClientSocket::InitClient(char* IP,UINT nPort)
{
	if (!Create())
	{
		return FALSE;
	}
	return Connect(IP,nPort);
}

typedef struct _tagHeader
{
	char szName[256];
	long nLen;
}HEADER,*LPHEADER;

// 2 发送文件（通信、关闭）
BOOL CClientSocket::SendFile(CString strPath)
{
	// 1 读取要发送的文件
	CFile file;
	file.Open(strPath,CFile::modeRead);
	long nLen=file.GetLength();
	CString strName=file.GetFileName();
	// 2 发送文件信息
	HEADER header={0};
	header.nLen=nLen;
	strcpy(header.szName,strName);
	if(!SendData((BYTE*)&header,sizeof(header)))
	{
		return FALSE;
	}
	// 3 发送文件数据
	BYTE* pData=(BYTE*)malloc(nLen);
	file.Read(pData,nLen);
	if (!SendData(pData,nLen))
	{
		return FALSE;
	}
	free(pData);
	file.Close();
	return TRUE;
}
// 3 发送数据(10分钟)
BOOL CClientSocket::SendData(BYTE* pData,long nLen)
{
	BYTE* pTmpData=pData;
	long nLeft=nLen;
	while(nLeft>0)
	{
		int nSend=Send(pTmpData,nLeft);
		if (nSend==SOCKET_ERROR)
		{
			return FALSE;
		}
		nLeft-=nSend;
		pTmpData+=nSend;
	}
	return TRUE;
}