#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define WIN32_LEAN_AND_MEAN
#include<windows.h>
#include<WinSock2.h>
#include<stdio.h>

int main()
{
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
	SOCKET client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == client_socket) {
		printf("socket初始化无效");
	}
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	int ret = connect(client_socket, (sockaddr*)&_sin,sizeof(sockaddr_in));
	if (ret == SOCKET_ERROR) {
		printf("连接失败");
	}
	char recvBuf[256] = {};
	int recLen = 0;
	recLen = recv(client_socket, recvBuf, 256, 0);
	if (recLen > 0) {
		printf("接收到的数据：%s", recvBuf);
	}
	closesocket(client_socket);
	WSACleanup();
	getchar();
	return 0;
}