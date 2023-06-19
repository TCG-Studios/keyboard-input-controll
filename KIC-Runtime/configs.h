#pragma once

#include <filesystem>
#include <string>

namespace Configurations
{
	const enum class configIndex : uint16_t
	{
		Config = 0,
		Modules,
		Profiles,
		Websocket,
		GUI,
		Count
	};
	const std::string CONFIGS[(uint16_t)configIndex::Count] = {
		"config.ini",
		"profiles.ini",
		"modules.ini",
		"websocket.ini",
		"GUI.ini"
	};

	Parser_base* configINIs = new IniParser[(uint8_t)configIndex::Count];

	Parser_base* pointerFromIndex(configIndex index) {
		return (Parser_base*)&configINIs[(uint16_t)index];
	}

	bool loadConfigs(std::string origin);
	
	
	std::filesystem::path getStartUpProfilePath();
	
	class profileManager {
	public:

		profileManager(const char* profileDir, const char* profileExtention)
			:seachDir(profileDir), pflExt(profileExtention)
		{ }

	private:
		std::string seachDir;
		const char* pflExt;
		std::vector<std::string*> profilePaths;
	public:
		
		void loadProfiles();
		
		void reloadProfiles();
		
		void freeProfiles();
	};
}