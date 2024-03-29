#include "Client-SideThread.h"

void clientSide::MessageSendHandler(
	TCHAR ipAddress[], 
	std::mutex& m, 
	std::condition_variable& cond, 
	bool& canWrite,
	currentPosition& pos,
	bool& escapeApp
)
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
	socketInfo.sin_port = htons(connectPort);

	if (connect(clientSocket, (SOCKADDR*)&socketInfo, sizeof(socketInfo)) == SOCKET_ERROR)
	{
		std::cout << "connect() in Client-SideTHread failedS";
		WSACleanup();
		return;
	}


	//std::cout << "YOU: ";
	setColor(Green, Black);
	std::cout << "CONNECTED TO THE USER\n";
	setColor(White, Black);

	std::unique_lock<std::mutex> locker(m);

	cond.wait(locker, [&canWrite]() {return canWrite; });

	////////////////////// sending information

	while (!escapeApp)
	{
		setColor(LightBlue, Black);
		std::cout << "YOU: ";
		setColor(White, Black);

		char buffer[200];
		std::cin.getline(buffer, 200);

		char exitCheck[] = "--escAll";
		if (buffer[0] == exitCheck[0])
		{
			bool isSame = true;
			for (int i = 0; i < 9; i++)
			{
				if (buffer[i] != exitCheck[i])
				{
					isSame = false;
					break;
				}
			}

			if (isSame)
				escapeApp = true;
		}

		send(clientSocket, buffer, 200, 0);

		pos.y++;
	}

	WSACleanup();
}