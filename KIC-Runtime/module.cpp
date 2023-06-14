#include "iWin.h"
#include "module.h"
#include "WindowBoxes.h"

bool Module::loadLibrary() {
	if (isLoaded())
		return false; // Already loaded
	
	h_Module = LoadLibraryA(s_libPath.c_str());
	if (h_Module != nullptr)
	{
		modules::setFlag(m_flag, modules::Flag::Loaded);
		return true;
	}
	
	// Error occurred while loading the module
	ifDebug(DebugBox(("Failed to load library: " + s_libPath).c_str()));
	return false;
}

bool Module::freeLibrary()
{
	if (!isLoaded())
		return false; // Not loaded

	if (FreeLibrary(h_Module) != 0)
	{
		h_Module = nullptr;
		modules::clearFlag(m_flag, modules::Flag::Loaded);
		return true;
	}

	// Error occurred while unloading the module
	ifDebug(DebugBox(("Failed to free library: " + s_libPath).c_str()));
	return false;
}

bool Module::reloadLibrary()
{
	if (freeLibrary())
		return loadLibrary();
	return false;
}

template <typename T>
fncptr<T> Module::getFunction(const char* functionName)
{
	assert(isLoaded() && "Module not loaded.");

	fncptr<T> function = reinterpret_cast<fncptr<T>>(GetProcAddress(h_Module, functionName));
	if (function == nullptr)
	{
		// Error occurred while retrieving the function
		ifDebug(DebugBox(("Failed to get function: " + std::string(functionName)).c_str()));
	}
	return function;
}