#include "Serve-SideThread.h"
#include "Client-SideThread.h"

int main()
{
	std::mutex m;

	setColor(Brown, Black);
	std::cout << "* You have to enter other's user's ip adress"
		<< "\n* Other user has to enter it too"
		<< "\n* Nothing will happen if other user doesn't enter your ip ";
	setColor(Red, Black);
	std::cout << "\n\nEnter other user's ip adress here: ";
	setColor(White, Black);

	TCHAR ipAddress[16];
	std::wcin.getline(ipAddress, 16);

	std::condition_variable cond;

	bool canWrite = false;

	currentPosition pos = { 0, 6 };

	std::thread ServerThread( serverSide::MessageListenHandler, 
		std::ref(m), 
		std::ref(cond), 
		std::ref(canWrite),
		std::ref(pos)
	);

	std::thread ClientThread(clientSide::MessageSendHandler, 
		ipAddress, 
		std::ref(m), 
		std::ref(cond), 
		std::ref(canWrite),
		std::ref(pos)
	);


	ClientThread.join();
	ServerThread.join();

	return 0;
}