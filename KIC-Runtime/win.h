#pragma once

// Debug defines
#ifdef _DEBUG
#	define ifDebug(code) code
#else
#	define ifDebug(code)
#endif // _DEBUG

// Defines

#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00

#define STRICT
#include <Windows.h>
#include <codecvt>
#include <locale>
#include <string>

ifDebug(
	HANDLE console = nullptr;
)

ifDebug(
	int conOut(std::string msg) {
	if (console != nullptr) {
		DWORD written;
		return WriteConsoleA(console, msg.c_str(), static_cast<DWORD>(msg.length()), &written, nullptr);
	}
}
)


#include "types.h"

#ifndef winBoxes
#define winBoxes

// debug boxes
int DebugBox(const char* msg, HWND window = NULL)
{
	return MessageBoxW(
		window,
		StringToLPCWSTR(
			"Debug Error: " + std::to_string(GetLastError()) + "\n" + msg + "\n\n" ),
		StringToLPCWSTR("Debug"),
		0);
}
int DebugBox(const std::string& msg, HWND window = NULL)
{ return DebugBox(msg,window); }


// Error Boxes
int ErrorBox(const char* msg, HWND wnd = NULL)
{
	return MessageBoxW(
		wnd,
		StringToLPCWSTR(
			"Error: " + std::to_string(GetLastError()) + "\n" + msg + "\n\n" ),
		StringToLPCWSTR("Error"),
		0);
}
int ErrorBox(const std::string& msg, HWND wnd = NULL)
{ return ErrorBox(msg, wnd); }


// Fatal Boxes
void FatalBox(const char* msg, HWND wnd = NULL)
{
	MessageBoxW(
		wnd,
		StringToLPCWSTR(
			"Fatal Error: " + std::to_string(GetLastError()) + "\n" + msg + "\n\n" ),
		StringToLPCWSTR("Fatal Error"),
		0);
	PostQuitMessage((uint32_t)GetLastError());
}
void FatalBox(const std::string& msg, HWND wnd = NULL) 
{ FatalBox(msg, wnd); }


#endif // winBoxes

#include "configs.h"
