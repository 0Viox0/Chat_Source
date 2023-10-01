#pragma once
#include "Includes.h"

//server-side thread function that will be in accept mode
namespace clientSide
{
	void MessageSendHandler(TCHAR ipAddress[]);
}