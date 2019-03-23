#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
void UDPServer()
{
	// 1 创建socket
	SOCKET hSockSvr=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (hSockSvr==INVALID_SOCKET)return;
    // 2 绑定
	SOCKADDR_IN addrSvr={0};
	addrSvr.sin_family=AF_INET;
	addrSvr.sin_port=htons(5678);
	addrSvr.sin_addr.S_un.S_addr=INADDR_ANY;
	bind(hSockSvr,(SOCKADDR*)&addrSvr,sizeof(addrSvr));
	// 3 通信
	// 3.1 服务器首先接收数据
	char szBuff[256]={0};
	SOCKADDR_IN addrClient={0};
	int nLen=sizeof(addrClient);
	int nRecv=recvfrom(hSockSvr,szBuff,256,0,
		(SOCKADDR*)&addrClient,&nLen);
	char *IP=inet_ntoa(addrClient.sin_addr);
	printf("%s:%s,%d\n",IP,szBuff,nRecv);
	// 3.2 然后将数据原样发送回客户端
	sendto(hSockSvr,szBuff,strlen(szBuff),0,
		(SOCKADDR*)&addrClient,sizeof(addrClient));
	// 4 关闭
	closesocket(hSockSvr);
	getchar();

}
int main()
{
	// 1 初始化socket库
	WSAData wd={0};
	WSAStartup(MAKEWORD(2,2),&wd);
	// 2 使用socket库
	UDPServer();
	// 3 卸载socket库
	WSACleanup();
	return 0;
}