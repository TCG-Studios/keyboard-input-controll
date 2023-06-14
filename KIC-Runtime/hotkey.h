#pragma once
#include <array>
#include "typedefs.h"

class hotkey
{
	template<typename ...args>
	hotkey(args... arg);
private:
	u16* keys;
	u8 keyCount;
};