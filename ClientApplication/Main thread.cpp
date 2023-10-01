#include "Serve-SideThread.h"
#include "Client-SideThread.h"

int main()
{
	std::thread ClientThread(clientSide::MessageSendHandler);
	std::thread ServerThread(serverSide::MessageListenHandler);

	ClientThread.join();
	ServerThread.join();

	return 0;
}