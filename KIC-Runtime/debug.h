#pragma once

#include "iWin.h"
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
