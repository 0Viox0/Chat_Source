#pragma once
#include "Includes.h"

class noWinsockDLLfoundException : public std::exception
{
public:
	noWinsockDLLfoundException() : msg("couldn't find winsock dll")
	{ }

	noWinsockDLLfoundException(const char* msg) : msg(msg)
	{ }
		
	const char* what();
	
private:
	const char* msg;
};