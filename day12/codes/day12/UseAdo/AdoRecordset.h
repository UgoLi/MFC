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
	// 4 获取字段的值
	void GetFieldValue(long nIndex,CString& strValue);
	// 5 记录集的指针操作
	void MoveFirst();
	void MoveLast();
	void MoveNext();
	void MovePrevious();
	BOOL IsBOF();
	BOOL IsEOF();
public:
	_RecordsetPtr m_pSet;
};

