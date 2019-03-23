#pragma once
#include "AdoDatabase.h"
class CAdoRecordset
{
public:
	CAdoRecordset(void);
	~CAdoRecordset(void);
	// 1 执行Sql语句
	BOOL OpenSql(CString strSql,CAdoDatabase *pDB);
	// 2 获取字段数量
	long GetFieldCount();
	// 3 获取字段的名称
	void GetFieldName(long nIndex,CString& strName);
public:
	_RecordsetPtr m_pSet;
};

