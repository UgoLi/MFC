#pragma once

// CServerSocket 命令目标

class CServerSocket : public CAsyncSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();
	// 1 初始化服务器(创建、绑定、监听)
	BOOL InitServer(UINT nPort);
	// 2 接收客户端连接、通信、关闭
	virtual void OnAccept(int nErrorCode);
	// 3 接收数据
	BOOL RecvData(CSocket& client,BYTE* pData,long nLen);

};


