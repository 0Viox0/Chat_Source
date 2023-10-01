#include "Serve-SideThread.h"

void serverSide::MessageListenHandler()
{
	SOCKET serverSocket, acceptSocket;
	int port = 55555;

	WORD wVersionRequired = MAKEWORD(2, 2);
	WSAData wsaData;

	if (WSAStartup(wVersionRequired, &wsaData))
	{
		std::cout << "the winsock dll not found!";
		return;
	}

	//obtaining ip of the host
		struct IPv4
		{
			unsigned char b1, b2, b3, b4;
		};

		IPv4 myIP;

		char szBuffer[1024];

		if (gethostname(szBuffer, sizeof(szBuffer)) == SOCKET_ERROR)
		{
			std::cout << "couldn't get a host name";
			return;
		}

		struct hostent* host = gethostbyname(szBuffer);
		if (host == NULL)
		{
			std::cout << "couldn't get a host data";
			return;
		}

		//Obtain the computer's IP
		myIP.b1 = ((struct in_addr*)(host->h_addr))->S_un.S_un_b.s_b1;
		myIP.b2 = ((struct in_addr*)(host->h_addr))->S_un.S_un_b.s_b2;
		myIP.b3 = ((struct in_addr*)(host->h_addr))->S_un.S_un_b.s_b3;
		myIP.b4 = ((struct in_addr*)(host->h_addr))->S_un.S_un_b.s_b4;
	
//////////////////////////////////////////////////////////////////////////////////
	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (serverSocket == INVALID_SOCKET)
	{
		std::cout << "coundn't create the socket!";
		WSACleanup();
		return;
	}

	sockaddr_in sockInfo;
	sockInfo.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &sockInfo.sin_addr.s_addr);
	sockInfo.sin_port = htons(port);

	//if (bind(serverSocket, (SOCKADDR*)&sockInfo, sizeof(sockInfo)) == SOCKET_ERROR)
	if (bind(serverSocket, (SOCKADDR*)(struct in_addr*)(host->h_addr), sizeof(sockInfo)) == SOCKET_ERROR)
	{
		std::cout << "bind() in server-sideThread failed";
		WSACleanup();
		return;
	}

	if (listen(serverSocket, 1) == SOCKET_ERROR)
	{
		std::cout << "listen() in server-SideThread failed";
		WSACleanup();
		return;
	}

	acceptSocket = accept(serverSocket, NULL, NULL);

	if (acceptSocket == INVALID_SOCKET)
	{
		std::cout << "accept() in Server-SideThread failed";
		WSACleanup();
		return;
	}




}