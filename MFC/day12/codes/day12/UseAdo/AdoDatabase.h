#pragma once
class CAdoDatabase
{
public:
	CAdoDatabase(void);
	~CAdoDatabase(void);
	BOOL OpenAccess(CString strPath);
	void Close();
	// ִ��Sql���Ĺ���
	void ExecuteSQL(CString strSql);

public:
	_ConnectionPtr m_pConn;
};

