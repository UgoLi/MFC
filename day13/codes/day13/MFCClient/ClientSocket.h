#pragma once

// CClientSocket 命令目标

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
	// 1 初始化客户端(创建、连接)
	BOOL InitClient(char* IP,UINT nPort);
    // 2 发送文件（通信、关闭）
	BOOL SendFile(CString strPath);
	// 3 发送数据
	BOOL SendData(BYTE* pData,long nLen);
};


