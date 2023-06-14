#pragma once
#include "iWin.h"

// debug boxes
int DebugBox(const char* msg, HWND window = NULL);


// Error Boxes
int ErrorBox(const char* msg, HWND wnd = NULL);


// Fatal Boxes
void FatalBox(const char* msg, HWND wnd = NULL);