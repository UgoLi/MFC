#include "StdAfx.h"
#include "AdoRecordset.h"


CAdoRecordset::CAdoRecordset(void)
{
}


CAdoRecordset::~CAdoRecordset(void)
{
}
BOOL CAdoRecordset::OpenSql(CString strSql,CAdoDatabase *pDB)
{
	// 1 ������¼������
	HRESULT nRet= m_pSet.CreateInstance(__uuidof(Recordset));
	if (FAILED(nRet))
	{
		return FALSE;
	}
	// 2 �򿪼�¼��
	nRet=m_pSet->Open(_variant_t(strSql),
		(IDispatch*)pDB->m_pConn,
		adOpenForwardOnly,adLockReadOnly,adCmdText);
	if (FAILED(nRet))
	{
		return FALSE;
	}
	return TRUE;
}
long CAdoRecordset::GetFieldCount()
{
	return m_pSet->Fields->GetCount();
}
void CAdoRecordset::GetFieldName(long nIndex,CString& strName)
{
	strName=(char*)m_pSet->Fields->GetItem(nIndex)->GetName();

}