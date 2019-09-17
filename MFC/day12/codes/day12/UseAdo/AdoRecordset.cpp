#include "StdAfx.h"
#include "AdoRecordset.h"


CAdoRecordset::CAdoRecordset(void)
{
}


CAdoRecordset::~CAdoRecordset(void)
{
}
BOOL CAdoRecordset::OpenSql(CString strSql,CAdoDatabase* m_db)
{
	// 1 ������¼������
	HRESULT nRet = m_pSet.CreateInstance(__uuidof(Recordset));
	if (FAILED(nRet))
	{
		return FALSE;
	}
	// 2 ����Open����
	nRet = m_pSet->Open(_variant_t(strSql),
		(IDispatch*)m_db->m_pConn,
		adOpenKeyset,adLockOptimistic,adCmdText);
	if (FAILED(nRet))
	{
		return FALSE;
	}
	return TRUE;
}
// 2 ��ȡ�ֶε�����
long CAdoRecordset::GetFieldCount()
{
	return m_pSet->Fields->GetCount();
}
// 3 �����ֶε�����ֵ����ȡ�ֶε�����
void CAdoRecordset::GetFieldName(long nIndex,CString& strName)
{
	strName = (char*)m_pSet->Fields->GetItem(nIndex)->GetName();
}
// 4 ��ȡ�ֶε�ֵ
void CAdoRecordset::GetFieldValue(long nIndex,CString& strValue)
{
	_variant_t varValue= m_pSet->Fields->GetItem(nIndex)->GetValue();
	if (varValue.vt == VT_NULL)
	{
		strValue="";
	} 
	else
	{
		strValue = (char*)(_bstr_t)varValue;
	}
}
// 5 ��¼����ָ�����
void CAdoRecordset::MoveFirst()
{
	m_pSet->MoveFirst();
}
void CAdoRecordset::MoveNext()
{
	m_pSet->MoveNext();
}
void CAdoRecordset::MovePrevious()
{
	m_pSet->MovePrevious();
}
void CAdoRecordset::MoveLast()
{
	m_pSet->MoveLast();
}
BOOL CAdoRecordset::IsBOF()
{
	return m_pSet->BOF;
}
BOOL CAdoRecordset::IsEOF()
{
	return m_pSet->adoEOF;
}

