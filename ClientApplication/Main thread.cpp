#include "Serve-SideThread.h"
#include "Client-SideThread.h"

int main()
{
	std::mutex m;

	setColor(Red, Black);
	std::cout << "Enter other user's ip address: ";
	setColor(White, Black);

	TCHAR ipAddress[16];
	std::wcin.getline(ipAddress, 16);

	std::condition_variable cond;

	bool canWrite = false;

	std::thread ServerThread(serverSide::MessageListenHandler, std::ref(m), std::ref(cond), std::ref(canWrite));
	std::thread ClientThread(clientSide::MessageSendHandler, ipAddress, std::ref(m), std::ref(cond), std::ref(canWrite));

	ClientThread.join();
	ServerThread.join();

	return 0;
}