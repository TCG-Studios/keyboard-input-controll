#include "types.h"
#include "hotkey.h"

template<typename ...args>
hotkey::hotkey(args... arg) {
	keys = new uint16_t[std::size(arg)];
	for (size_t i = 0; i < std::size(arg); i++) {
		keys[i] = std::get<i>(arg);
	}
}