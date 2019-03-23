// ClientSocket.cpp : ʵ���ļ�
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


// CClientSocket ��Ա����
// 1 ��ʼ���ͻ���(����������)
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

// 2 �����ļ���ͨ�š��رգ�
BOOL CClientSocket::SendFile(CString strPath)
{
	// 1 ��ȡҪ���͵��ļ�
	CFile file;
	file.Open(strPath,CFile::modeRead);
	long nLen=file.GetLength();
	CString strName=file.GetFileName();
	// 2 �����ļ���Ϣ
	HEADER header={0};
	header.nLen=nLen;
	strcpy(header.szName,strName);
	if(!SendData((BYTE*)&header,sizeof(header)))
	{
		return FALSE;
	}
	// 3 �����ļ�����
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
// 3 ��������(10����)
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