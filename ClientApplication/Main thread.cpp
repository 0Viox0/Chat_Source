#include "Serve-SideThread.h"
#include "Client-SideThread.h"

int main()
{
	std::mutex m;

	setColor(Brown, Black);
	std::cout << "* You have to enter other's user's ip adress"
		<< "\n* Other user has to enter it too"
		<< "\n* Nothing will happen if other user doesn't enter your ip"
		<< "\n* Type '--escAll' to exit the app (other user has to press Enter to confirm)";
	setColor(Red, Black);
	std::cout << "\n\nEnter other user's ip adress here: ";
	setColor(White, Black);

	TCHAR ipAddress[16];
	std::wcin.getline(ipAddress, 16);

	std::condition_variable cond;

	bool canWrite = false;
	bool escapeApp = false;

	currentPosition pos = { 0, 7 };
	std::thread ServerThread( serverSide::MessageListenHandler, 
		std::ref(m), 
		std::ref(cond), 
		std::ref(canWrite),
		std::ref(pos),
		std::ref(escapeApp)
	);

	std::thread ClientThread(clientSide::MessageSendHandler, 
		ipAddress, 
		std::ref(m), 
		std::ref(cond), 
		std::ref(canWrite),
		std::ref(pos),
		std::ref(escapeApp)
	);

	ClientThread.join();
	ServerThread.join();

	setColor(Red, Black);
	std::cout << "\ndisconnected from the user";
	setColor(White, Black);

	return 0;
}