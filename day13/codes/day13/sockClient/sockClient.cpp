#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
void UDPClient()
{
	// 1 创建
	SOCKET hSockClient=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (hSockClient==INVALID_SOCKET)return;
	// 2 通信
	// 2.1 首先发送数据
	SOCKADDR_IN addrSvr={0};
	addrSvr.sin_family=AF_INET;
	addrSvr.sin_port=htons(5678);
	addrSvr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	char szSend[]="Hello World";
	sendto(hSockClient,szSend,strlen(szSend),0,
		(SOCKADDR*)&addrSvr,sizeof(addrSvr));
	// 2.2 然后接收数据
	char szBuff[256]={0};
	int nLen=sizeof(addrSvr);
	int nRecv=recvfrom(hSockClient,szBuff,256,0,
		(SOCKADDR*)&addrSvr,&nLen);
	printf("%s,%d\n",szBuff,nRecv);
	// 3 关闭
	closesocket(hSockClient);
	getchar();

}
int main()
{
	// 1 初始化socket库
	WSAData wd={0};
	WSAStartup(MAKEWORD(2,2),&wd);
	// 2 使用socket库
	UDPClient();
	// 3 卸载socket库
	WSACleanup();
	return 0;
}