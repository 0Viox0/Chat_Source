#include "Serve-SideThread.h"

void GetIpAddress(TCHAR ipAddress[], int bufferSize) 
{
    #pragma warning(disable : 4996) // to use gethostname() and getaddrinfo()

    WSADATA wData;
    if (WSAStartup(MAKEWORD(2, 2), &wData) != 0) 
    {
        ipAddress[0] = _T('\0');
        return;
    }

    // Get the host name
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) != 0) 
    {
        WSACleanup();
        ipAddress[0] = _T('\0');
        return;
    }

    // Get the host information
    struct addrinfo* result = NULL;
    struct addrinfo* ptr = NULL;
    struct addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo(hostname, NULL, &hints, &result) != 0) 
    {
        WSACleanup();
        ipAddress[0] = _T('\0');
        return;
    }

    // Iterate through the address list and find the IP address
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) 
    {
        void* addr;

        if (ptr->ai_family == AF_INET) // IPv4 address
        {
            struct sockaddr_in* ipv4 = (struct sockaddr_in*)ptr->ai_addr;
            addr = &(ipv4->sin_addr);
        }
        else // IPv6 address
        { 
            struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)ptr->ai_addr;
            addr = &(ipv6->sin6_addr);
        }

        // Convert the IP address to a string
        if (InetNtop(ptr->ai_family, addr, ipAddress, bufferSize) != NULL) 
        {
            break; // IP address successfully retrieved
        }
    }

    freeaddrinfo(result);
    WSACleanup();
}

void serverSide::MessageListenHandler(
    std::mutex& m, 
    std::condition_variable& cond,
    bool& canWrite
)
{
	SOCKET serverSocket, acceptSocket;

    TCHAR ipAddress[16];
	GetIpAddress(ipAddress, 16);
	int port = 55555;

	WORD wVersionRequired = MAKEWORD(2, 2);
	WSAData wsaData;

	if (WSAStartup(wVersionRequired, &wsaData))
	{
		std::cout << "the winsock dll not found!";
		return;
	}

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
	InetPton(AF_INET, ipAddress, &sockInfo.sin_addr.s_addr);
	sockInfo.sin_port = htons(port);

	if (bind(serverSocket, (SOCKADDR*)&sockInfo, sizeof(sockInfo)) == SOCKET_ERROR)
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
    else
    {
        //std::cout << "\nOTHER-USER: ";
        setColor(Green, Black);
        std::cout << "CONNECTION ACCEPTED\n";
        setColor(White, Black);

        canWrite = true;
    }
    
    cond.notify_one();

    ////////////////////// recieving information

    
    while (true)
    {
        char buffer[200];

        recv(acceptSocket, buffer, 200, 0);

        setColor(LightMagenta, Black);
        std::cout << "\nOTHER-USER: ";
        setColor(White, Black);
        std::cout << buffer;
    }
    
}