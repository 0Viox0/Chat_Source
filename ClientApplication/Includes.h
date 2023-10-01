#pragma once

#include "stdafx.h"
#include <WinSock2.h>
#include <ws2tcpip.h>

#include <exception>

#include <thread>
#include <string>
#include <iostream>
#include <Windows.h>
#include <mutex>
#include <conio.h>
#include <condition_variable>

enum ConsoleColor {
	Black = 0, Blue = 1, Green = 2, Cyan = 3, Red = 4, Magenta = 5, Brown = 6,
	LightGray = 7, DarkGray = 8, LightBlue = 9, LightGreen = 10, LightCyan = 11,
	LightRed = 12, LightMagenta = 13, Yellow = 14, White = 15
};