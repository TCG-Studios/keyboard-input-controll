#pragma once

// Debug defines
#ifdef _DEBUG
#	define ifDebug(code) code
#else
#	define ifDebug(code)
#endif // _DEBUG

#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00

#define STRICT
#include <Windows.h>