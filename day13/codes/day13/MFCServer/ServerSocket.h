#pragma once

// CServerSocket ����Ŀ��

class CServerSocket : public CAsyncSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();
	// 1 ��ʼ��������(�������󶨡�����)
	BOOL InitServer(UINT nPort);
	// 2 ���տͻ������ӡ�ͨ�š��ر�
	virtual void OnAccept(int nErrorCode);
	// 3 ��������
	BOOL RecvData(CSocket& client,BYTE* pData,long nLen);

};


