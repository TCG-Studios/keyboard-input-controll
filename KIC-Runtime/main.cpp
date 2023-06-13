// Debug
#ifdef _DEBUG

#	include <string>

#endif // _DEBUG


// std Includes

// Debug Includes

// Includes
#include "win.h"


HHOOK keyboardHook;
bool hideInput = true;
HANDLE deviceHandle = NULL;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		KBDLLHOOKSTRUCT* keyboardStruct = (KBDLLHOOKSTRUCT*)lParam;

		if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
		{
			// Display key ID and device ID
			ifDebug(conOut("Key ID: " + std::to_string((uint32_t)keyboardStruct->vkCode) + "\n"));
			ifDebug(conOut("Device ID: " + std::to_string((uintptr_t)deviceHandle) + "\n"));
		}
	}

	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

void RegisterRawInputDevices(HWND hwnd)
{
	RAWINPUTDEVICE rawInputDevice;
	rawInputDevice.usUsagePage = 0x01;  // Generic desktop controls
	rawInputDevice.usUsage = 0x06;      // Keyboard
	rawInputDevice.dwFlags = RIDEV_INPUTSINK;
	rawInputDevice.hwndTarget = hwnd;

	if (!RegisterRawInputDevices(&rawInputDevice, 1, sizeof(rawInputDevice)))
	{
		ifDebug(conOut("Failed to register raw input devices!\n"));
		ErrorBox("Failed to register raw input devices!\n");
	}
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_INPUT)
	{
		UINT dataSize = 0;
		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));

		LPBYTE inputData = new BYTE[dataSize];
		if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, inputData, &dataSize, sizeof(RAWINPUTHEADER)) == dataSize)
		{
			RAWINPUT* rawInput = (RAWINPUT*)inputData;
			if (rawInput->header.dwType == RIM_TYPEKEYBOARD)
			{
				deviceHandle = rawInput->header.hDevice;
			}
		}
		
		delete[] inputData;
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, 0, 0);
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd )
{
	ifDebug(
		AllocConsole();
		console = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	)

	// Create a hidden window to receive raw input messages
	WNDCLASS wndClass;
	wndClass.style = 0;
	wndClass.lpfnWndProc = WindowProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = GetModuleHandle(NULL);
	wndClass.hIcon = NULL;
	wndClass.hCursor = NULL;
	wndClass.hbrBackground = NULL;
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = L"HiddenWindowClass";

	ATOM atom = RegisterClass(&wndClass);
	if (atom == 0)
	{
		ifDebug(conOut("Failed to register window class!\n"));
		return 1;
	}

	HWND hiddenWindow = CreateWindowEx(0, wndClass.lpszClassName, NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, NULL, NULL);
	if (hiddenWindow == NULL)
	{
		ifDebug(conOut("Failed to create hidden window!\n"));
		return 1;
	}

	RegisterRawInputDevices(hiddenWindow);

	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
	if (keyboardHook == NULL)
	{
		ifDebug(conOut("Failed to install keyboard hook!\n"));
		return 1;
	}

	// Message loop to keep the program running
	MSG message;
	while (GetMessage(&message, NULL, 0, 0) != WM_QUIT)
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	// Unhook the keyboard hook
	UnhookWindowsHookEx(keyboardHook);
	return 0;
}
