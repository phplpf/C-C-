#pragma once
#include "AdoDatabase.h"
class CAdoRecordset
{
public:
	CAdoRecordset(void);
	~CAdoRecordset(void);
	// 1 �򿪼�¼��
	BOOL OpenSql(CString strSql,CAdoDatabase* m_db);
	// 2 ��ȡ�ֶε�����
	long GetFieldCount();
	// 3 �����ֶε�����ֵ����ȡ�ֶε�����
	void GetFieldName(long nIndex,CString& strName);
	// 4 ��ȡ�ֶε�ֵ
	void GetFieldValue(long nIndex,CString& strValue);
	// 5 ��¼����ָ�����
	void MoveFirst();
	void MoveNext();
	void MovePrevious();
	void MoveLast();
	BOOL IsBOF();
	BOOL IsEOF();
public:
	_RecordsetPtr m_pSet;
};

