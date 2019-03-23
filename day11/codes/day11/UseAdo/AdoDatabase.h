#pragma once
class CAdoDatabase
{
public:
	CAdoDatabase(void);
	~CAdoDatabase(void);
	// 1 连接Access数据库
	BOOL OpenAccess(CString strPath);
	// 2 关闭数据库
	void Close();
public:
	_ConnectionPtr m_pConn;
};

