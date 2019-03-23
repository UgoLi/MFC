#include <stdio.h>
#include <afxwin.h>

// �ļ���д����ʾ
void UseCFile()
{
	CFile file;
	try
	{
		// 1 �½�����ļ�
		file.Open("d:/mfcfile.txt",CFile::modeCreate|CFile::modeReadWrite);
		// 2 д�ļ�
		char szWrite[]="Hello World";
		file.Write(szWrite,strlen(szWrite));
		//��ȡ�ļ�����֮ǰ�����Ƚ��ļ�ָ���ƶ����ļ���ͷ
		file.SeekToBegin();
		// ���ļ�
		char szBuff[256]={0};
		int nRead=file.Read(szBuff,256);
		printf("����:%s,����:%d\n",szBuff,nRead);
		// 3 �ر��ļ�
		file.Close();
	}
	catch (CFileException* e)
	{
		// �쳣����
	}
	
}
void UseCFileFind(CString strPath)
{
	CFileFind find;
	BOOL bRet=find.FindFile(strPath+"/*.*");
	while (bRet)
	{
		bRet=find.FindNextFile();
		CString strName=find.GetFileName();
		if (find.IsDirectory())
		{
			printf("[%s]\n",strName);
		} 
		else
		{
			printf("%s\n",strName);
		}

	}
	find.Close();
}
int main()
{
	UseCFile();
	UseCFileFind("d:");
	return 0;
}
