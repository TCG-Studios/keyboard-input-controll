#include "hotkey.h"


template<typename ...args>
hotkey::hotkey(args... arg) {
	keys = new u16[std::size(arg)];
	for (u64 i = 0; i < std::size(arg); i++) {
		keys[i] = std::get<i>(arg);
	}
}