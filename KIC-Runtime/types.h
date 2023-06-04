#pragma once

// Function to convert std::string to LPCWSTR
LPCWSTR StringToLPCWSTR(const char* msg) {
    int wideStrLen = MultiByteToWideChar(CP_UTF8, 0, msg, -1, nullptr, 0);
    std::wstring wideStr(wideStrLen, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, msg, -1, &wideStr[0], wideStrLen);
    return wideStr.c_str();
}

LPCWSTR StringToLPCWSTR(const std::string& msg) {
	return StringToLPCWSTR(msg);
}