#pragma once
#include "Includes.h"

#include "SetColorFile.h"
#include "GotoXY.h"

//server-side thread function that will be in accept mode
namespace serverSide
{
	void MessageListenHandler(
		std::mutex&, 
		std::condition_variable&,
		bool& canWrite,
		currentPosition& cur
	);
}