#pragma once
#include "AdoDatabase.h"
class CAdoRecordset
{
public:
	CAdoRecordset(void);
	~CAdoRecordset(void);
	// 1 ִ��Sql���
	BOOL OpenSql(CString strSql,CAdoDatabase *pDB);
	// 2 ��ȡ�ֶ�����
	long GetFieldCount();
	// 3 ��ȡ�ֶε�����
	void GetFieldName(long nIndex,CString& strName);
public:
	_RecordsetPtr m_pSet;
};

