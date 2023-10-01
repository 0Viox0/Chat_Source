#pragma once
#include "Includes.h"
#include "SetColorFile.h"

//server-side thread function that will be in accept mode
namespace serverSide
{
	void MessageListenHandler(std::mutex&);
}