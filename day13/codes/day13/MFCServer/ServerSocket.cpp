// ServerSocket.cpp : ʵ���ļ�
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


// CServerSocket ��Ա����

BOOL CServerSocket::InitServer(UINT nPort)
{
	if (!Create(nPort))//�����Ͱ�
	{
		return FALSE;
	}
	return Listen();//����
}
typedef struct _tagHeader
{
   char szName[256];
   long nLen;
}HEADER,*LPHEADER;
BOOL CServerSocket::RecvData(CSocket& client,BYTE* pData,long nLen)
{
	BYTE* pTmpData=pData;
	long nLeft=nLen;//ʣ��Ļ�û�н��յ����ݵĳ���
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
	// ��������
	CSocket client;
	Accept(client);
	// ͨ��(�����ļ�)
	// 1 ���Ƚ����ļ���Ϣ(�ļ����ƺͳ���)
	HEADER header={0};
	if (!RecvData(client,(BYTE*)&header,sizeof(header)))
	{
		AfxMessageBox("�����ļ���Ϣʧ�ܣ�");
		return;
	}
	// 2 Ȼ������ļ�����
	BYTE* pData=(BYTE*)malloc(header.nLen);
	if (!RecvData(client,pData,header.nLen))
	{
		AfxMessageBox("�����ļ�����ʧ�ܣ�");
		return;
	}
	// 3 ���ļ����浽������(д�ļ�����)
	CFile file;
	CString strPath="d:/";
	strPath+=header.szName;
	file.Open(strPath,CFile::modeCreate|CFile::modeWrite);
	file.Write(pData,header.nLen);
	file.Close();
	free(pData);
	// �ر�
	client.Close();
	CAsyncSocket::OnAccept(nErrorCode);
}
