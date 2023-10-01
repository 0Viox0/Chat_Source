#include "Serve-SideThread.h"
#include "Client-SideThread.h"

int main()
{
	std::cout << "what is ip address you want to send to? : ";

	TCHAR ipAddress[16];
	std::wcin.getline(ipAddress, 16);

	std::thread ClientThread(clientSide::MessageSendHandler, ipAddress);
	//std::thread ServerThread(serverSide::MessageListenHandler);

	ClientThread.join();
	//ServerThread.join();

	return 0;
}