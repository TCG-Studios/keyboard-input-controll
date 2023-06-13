#include "win.h"
#include "module.h"
#include "hotkey.h"
#include "ini.h"
#include "configs.h"


/*
* 
* Profile Manager
* 
*/
typedef Configurations::profileManager pflMan;


void pflMan::loadProfiles()
{
	for (const auto& entry : fs::directory_iterator("./profiles/"))
	{
		if (entry.is_regular_file() && entry.path().extension().string() == pflExt)
		{
			std::string* g = new std::string(entry.path().string());
			profilePaths.push_back(g);
		}
	}
}
void pflMan::reloadProfiles()
{
	for (size_t i = 0; i < profilePaths.size(); i++)
	{
		delete[] profilePaths[i];
	}
	loadProfiles();
}

void pflMan::freeProfiles()
{
	for (size_t i = 0; i < profilePaths.size(); i++)
	{
		delete[] profilePaths[i];
	}
}

/*
* 
* 
* CONFIGS
* 
* 
*/
bool Configurations::loadConfigs(std::string origin) {
	for (uint16_t i = (uint16_t)configIndex::Config; i < (uint16_t)configIndex::Count; i++)
	{
		try
		{
			auto p = static_cast<IniParser*>(&configINIs[i]);
			p->read(origin + "config/" + CONFIGS[i]);
			p->validate();
		}
		catch (const std::runtime_error& e) {
			ifDebug(
				conOut("Error!\n" + (std::string)e.what());
			)
				ErrorBox("Error While Loading Config: " + CONFIGS[i] + "!\n" + (std::string)e.what() + "\n\nContinuing with default configuration...");
			// TODO: hard code standard configs if they don't exist
		}
	}
	return true;
}

std::filesystem::path Configurations::getStartUpProfilePath()
{
	return static_cast<IniParser*>(pointerFromIndex(configIndex::Profiles))->
		get<std::string>("StartProfile", "Profile_Path", "");
}

