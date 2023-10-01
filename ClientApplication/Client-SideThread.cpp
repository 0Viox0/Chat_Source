#include "Client-SideThread.h"

void clientSide::MessageSendHandler(TCHAR ipAddress[])
{
	SOCKET clientSocket;

	int connectPort = 55555;

	WORD wVersionRequired = MAKEWORD(2, 2);
	WSAData wsaData;

	if (WSAStartup(wVersionRequired, &wsaData))
	{
		std::cout << "the winsock dll not found!";
		return;
	}

	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (clientSocket == INVALID_SOCKET)
	{
		std::cout << "socket() in Client-SideThread failed";
		WSACleanup();
		return;
	}

	sockaddr_in socketInfo;
	socketInfo.sin_family = AF_INET;
	InetPton(AF_INET, ipAddress, &socketInfo.sin_addr.s_addr);
	//InetPton(AF_INET, _T("192.168.0.177"), &socketInfo.sin_addr.s_addr);
	socketInfo.sin_port = htons(connectPort);

	std::cout << "\ntrying to connect to the server..";

	if (connect(clientSocket, (SOCKADDR*)&socketInfo, sizeof(socketInfo)) == SOCKET_ERROR)
	{
		std::cout << "connect() in Client-SideTHread failedS";
		WSACleanup();
		return;
	}

	std::cout << "\n.\nconnected to the server!\n";
}