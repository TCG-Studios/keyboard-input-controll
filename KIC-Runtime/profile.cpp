#include "hotkey.h"
#include "module.h"
#include "profile.h"

static bool find(const std::string& path, const std::vector<Module*> modds) {
	for (const auto modd : modds)
	{
		if(modd->getPath() == path)
			return true;
	}
	return false;
}

profile::profile(const std::filesystem::path& a_modules... )
{
	for (auto& f_module : a_modules)
	{
		if (!find(f_module.string(), modules::selectedModules))
		{
			Module* mod = new Module(f_module);
			modules::selectedModules.push_back(mod);
		}
	}
}
