#pragma once

#include "ini.h"

#include <filesystem>
#include <string>

namespace Configurations
{
	const enum configIndex : uint8_t
	{
		Config = 0,
		Modules,
		Profiles,
		Websocket,
		GUI,
		Count
	};
	const std::string CONFIGS[configIndex::Count] = {
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

	bool loadConfigs(std::string origin) {
		
		try
		{
			for (uint16_t i = Config; i < Count; i++)
			{
				auto p = static_cast<IniParser*>(&configINIs[i]);
				p->read(origin + CONFIGS[i]);
				p->validate();
			}
		}
		catch (const std::runtime_error& e) {
			ifDebug(
				conOut("Error!\n" + (std::string)e.what());
			)
			ErrorBox("Error While Loading Configs!\n" + (std::string)e.what() + "\nContinuing...");
		}
		return true;
	}
	
	
	std::filesystem::path getStartUpProfilePath()
	{
		return static_cast<IniParser*>(pointerFromIndex(configIndex::Profiles))->
			get<std::string>("StartProfile", "Profile_Path" , "");
	}
	
	namespace profiles {
		std::string extentions[] = {".pf"};
		
		std::vector<std::string*> profilePaths;

		std::string relPath;
		void loadProfiles() 
		{
			for (const auto& entry : fs::directory_iterator(relPath))
			{
				if (entry.is_regular_file() && std::find(std::begin(extentions), std::end(extentions), entry.path().extension().string()) != NULL)
				{
					std::string* g = new std::string(entry.path().string());
					profilePaths.push_back(g);
				}
			}
		}
		void reloadProfiles() 
		{
			for (size_t i = 0; i < profilePaths.size(); i++)
			{
				delete[] profilePaths[i];
			}
			loadProfiles();
		}
		
		
	}
}