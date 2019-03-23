#include <stdio.h>
#include <afxwin.h>

// д����(�洢)
void Store()
{
	CFile file;
	file.Open("d:/serial.dat",CFile::modeCreate|CFile::modeWrite);
	CArchive ar(&file,CArchive::store);
	ar<<100<<12.25<<'A';
	ar.Close();
	file.Close();
}
// �����������أ�
void Load()
{
	CFile file;
	file.Open("d:/serial.dat",CFile::modeRead);
	CArchive ar(&file,CArchive::load);
	int nValue=0;
	double dValue=0;
	char cValue;
	ar>>nValue>>dValue>>cValue;
	ar.Close();
	file.Close();
	printf("%d,%f,%c",nValue,dValue,cValue);
}

int main()
{
	Store();
	Load();

	return 0;
}