#include "Serve-SideThread.h"
#include "Client-SideThread.h"

int main()
{
	std::mutex m;

	std::thread ServerThread(serverSide::MessageListenHandler, std::ref(m));

	setColor(Red, Black);
	std::cout << "Enter other user's ip address: ";
	setColor(White, Black);

	TCHAR ipAddress[16];
	std::wcin.getline(ipAddress, 16);

	std::thread ClientThread(clientSide::MessageSendHandler, ipAddress, std::ref(m));

	ClientThread.join();
	ServerThread.join();

	return 0;
}