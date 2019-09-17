#include <stdio.h>
#include <afxwin.h>
void UseCFile()
{
	CFile file;
	try
	{
		// 1 �½�����ļ�
		CFile file;
		file.Open("d:/mfcfile.txt",CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
		// 2 д����
		file.SeekToEnd();
		char szBuff[]="Hello World";
		file.Write(szBuff,strlen(szBuff));
		// ������
		file.SeekToBegin();
		char szRead[256]={0};
		int nRead = file.Read(szRead,256);
		printf("%s,%d\n",szRead,nRead);
		// 3 �ر��ļ�
		file.Close();

	}
	catch (CFileException* e)
	{
		//�쳣����
	}
	
}

void UseCFileFind(CString strPath)
{
	CFileFind find;
	// 1 ��ʼ����
	BOOL bRet=find.FindFile(strPath+"/*.*");
	while (bRet)
	{
		bRet = find.FindNextFile();
		//CString strName=find.GetFileName();
		strPath = find.GetFilePath();
		if(find.IsDots())continue;
		if (find.IsDirectory())
		{
			printf("[%s]\n",strPath);
			UseCFileFind(strPath);
		}
		else
		{
			printf("%s\n",strPath);
		}
	}
	// �رղ���
	find.Close();

}

int main()
{
	//UseCFile();
	UseCFileFind("d:");
	return 0;
}