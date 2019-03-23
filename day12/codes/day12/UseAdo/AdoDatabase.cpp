#include "StdAfx.h"
#include "AdoDatabase.h"


CAdoDatabase::CAdoDatabase(void)
{
}


CAdoDatabase::~CAdoDatabase(void)
{
	Close();
}
BOOL CAdoDatabase::OpenAccess(CString strPath)
{
	// 1 �������Ӷ���
	HRESULT nRet=m_pConn.CreateInstance(__uuidof(Connection));
	if (FAILED(nRet))
	{
		return FALSE;
	}
	// 2 �������ݿ�
	CString strConn;
	strConn.Format("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=%s",
		strPath);
	nRet=m_pConn->Open(_bstr_t(strConn),"","",-1);
	if (FAILED(nRet))
	{
		return FALSE;
	}
	return TRUE;
}
void CAdoDatabase::Close()
{
	m_pConn->Close();
}
void CAdoDatabase::OpenSql(CString strSql)
{
	m_pConn->Execute(_bstr_t(strSql),NULL,adCmdText);
}