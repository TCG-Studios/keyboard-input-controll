#include "types.h"
#include "WindowBoxes.h"


int DebugBox(const char* msg, HWND window)
{
	return MessageBoxW(
		window,
		StringToLPCWSTR(
			("Debug Error: " + std::to_string(GetLastError()) + "\n" + msg + "\n\n").c_str()),
		StringToLPCWSTR("Debug"),
		0);
}

int ErrorBox(const char* msg, HWND wnd)
{
	return MessageBoxW(
		wnd,
		StringToLPCWSTR((
			"Error: " + std::to_string(GetLastError()) + "\n" + msg + "\n\n").c_str()),
		StringToLPCWSTR("Error"),
		0);
}

void FatalBox(const char* msg, HWND wnd)
{
	MessageBoxW(
		wnd,
		StringToLPCWSTR(
			("Fatal Error: " + std::to_string(GetLastError()) + "\n" + msg + "\n\n").c_str()),
		StringToLPCWSTR("Fatal Error"),
		0);
	PostQuitMessage((uint32_t)GetLastError());
}