#pragma once
#include <vector>
#include <unordered_map>

class profile
{
public:
	profile(const std::filesystem::path&...);
private:
	std::unordered_map<hotkey*, std::string> p_hotkeys;
};

