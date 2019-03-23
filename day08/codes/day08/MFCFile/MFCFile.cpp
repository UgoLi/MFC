#include <stdio.h>
#include <afxwin.h>

// 文件读写的演示
void UseCFile()
{
	CFile file;
	try
	{
		// 1 新建或打开文件
		file.Open("d:/mfcfile.txt",CFile::modeCreate|CFile::modeReadWrite);
		// 2 写文件
		char szWrite[]="Hello World";
		file.Write(szWrite,strlen(szWrite));
		//读取文件内容之前，首先将文件指针移动到文件开头
		file.SeekToBegin();
		// 读文件
		char szBuff[256]={0};
		int nRead=file.Read(szBuff,256);
		printf("内容:%s,长度:%d\n",szBuff,nRead);
		// 3 关闭文件
		file.Close();
	}
	catch (CFileException* e)
	{
		// 异常处理
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
