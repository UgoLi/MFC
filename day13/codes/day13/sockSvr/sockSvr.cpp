#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
void UDPServer()
{
	// 1 ����socket
	SOCKET hSockSvr=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (hSockSvr==INVALID_SOCKET)return;
    // 2 ��
	SOCKADDR_IN addrSvr={0};
	addrSvr.sin_family=AF_INET;
	addrSvr.sin_port=htons(5678);
	addrSvr.sin_addr.S_un.S_addr=INADDR_ANY;
	bind(hSockSvr,(SOCKADDR*)&addrSvr,sizeof(addrSvr));
	// 3 ͨ��
	// 3.1 ���������Ƚ�������
	char szBuff[256]={0};
	SOCKADDR_IN addrClient={0};
	int nLen=sizeof(addrClient);
	int nRecv=recvfrom(hSockSvr,szBuff,256,0,
		(SOCKADDR*)&addrClient,&nLen);
	char *IP=inet_ntoa(addrClient.sin_addr);
	printf("%s:%s,%d\n",IP,szBuff,nRecv);
	// 3.2 Ȼ������ԭ�����ͻؿͻ���
	sendto(hSockSvr,szBuff,strlen(szBuff),0,
		(SOCKADDR*)&addrClient,sizeof(addrClient));
	// 4 �ر�
	closesocket(hSockSvr);
	getchar();

}
int main()
{
	// 1 ��ʼ��socket��
	WSAData wd={0};
	WSAStartup(MAKEWORD(2,2),&wd);
	// 2 ʹ��socket��
	UDPServer();
	// 3 ж��socket��
	WSACleanup();
	return 0;
}