#pragma once
class CAdoDatabase
{
public:
	CAdoDatabase(void);
	~CAdoDatabase(void);
	// 1 ����Access���ݿ�
	BOOL OpenAccess(CString strPath);
	// 2 �ر����ݿ�
	void Close();
	// 3 ִ��Sql���
	void OpenSql(CString strSql);
public:
	_ConnectionPtr m_pConn;
};

