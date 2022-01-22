#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define WIN32_LEAN_AND_MEAN
#include<windows.h>
#include<WinSock2.h>
#include<stdio.h>

int main()
{
	WORD ver = MAKEWORD(2,2);
	WSADATA dat;
	WSAStartup(ver,&dat);
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(_sock, (sockaddr*)&_sin, sizeof(_sin)) == SOCKET_ERROR) {
		printf("绑定失败\n");
	}
	if (listen(_sock, 5) == SOCKET_ERROR) {
		printf("监听失败\n");
	}
	sockaddr_in clientAddr = {};
	int nAddrLen = sizeof(sockaddr_in);
	SOCKET _clientSock = INVALID_SOCKET;
	char msgbuf[] = "hello i am server";
	while (true) {
		_clientSock = accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);
		if (_clientSock == INVALID_SOCKET) {
			printf("连接无效");
		}
		printf("新客户端接入，IP为：%s\n",inet_ntoa(clientAddr.sin_addr));
		send(_clientSock, msgbuf, strlen(msgbuf) + 1, 0);
	}
	closesocket(_sock);
	WSACleanup();
	return 0;
}