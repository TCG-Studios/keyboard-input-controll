#include "WindowBoxes.h"
#include "typedefs.h"
#include "module.h"


modules::Flag modules::operator|(modules::Flag lhs, modules::Flag rhs) {
	return static_cast<modules::Flag>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
}

modules::Flag modules::operator&(modules::Flag lhs, modules::Flag rhs) {
	return static_cast<modules::Flag>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
}

modules::Flag modules::operator^(modules::Flag lhs, modules::Flag rhs) {
	return static_cast<modules::Flag>(static_cast<uint8_t>(lhs) ^ static_cast<uint8_t>(rhs));
}

bool modules::operator==(modules::Flag lhs, modules::Flag rhs) {
	return static_cast<uint8_t>(lhs) == static_cast<uint8_t>(rhs);
}

bool modules::operator!=(modules::Flag lhs, modules::Flag rhs) {
	return static_cast<uint8_t>(lhs) != static_cast<uint8_t>(rhs);
}

modules::Flag modules::operator~(modules::Flag lhs) {
	return static_cast<modules::Flag>(~static_cast<uint8_t>(lhs));
}

modules::Flag modules::createFlag(uint8_t value) {
	return static_cast<modules::Flag>(value);
}

bool modules::hasFlag(modules::Flag flag, const modules::Flag checkFlag) {
	return (flag & checkFlag) == checkFlag;
}

void modules::setFlag(modules::Flag& flag, modules::Flag setFlag) {
	flag = flag | setFlag;
}

void modules::clearFlag(modules::Flag& flag, const modules::Flag clearFlag) {
	flag = flag & ~clearFlag;
}

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
	return false;
}

bool Module::reloadLibrary()
{
	if (freeLibrary())
		return loadLibrary();
	return false;
}

template <typename T>
std::function<T()> Module::getFunction(const char* functionName)
{
	assert(isLoaded() && "Module not loaded.");

	fncptr<T> function = reinterpret_cast<fncptr<T>>(GetProcAddress(h_Module, functionName));
	if (function == nullptr)
	{
		// Error occurred while retrieving the function
	}
	return std::function<T()>(function);
}

void modules::LoadAllSelectedModules() {
	for (const auto sm : modules::selectedModules)
	{
		if (!sm->isLoaded())
			sm->loadLibrary();
	}
}
void modules::freeAllSelectedModules() {
	for (const auto sm : modules::selectedModules)
	{
		if (sm->isLoaded())
			sm->freeLibrary();
	}
}
void modules::initAllSelectedModules() {
	for (const auto sm : modules::selectedModules)
	{
		if (sm->isLoaded())
		{
			auto initFnc = sm->getFunction<int>("ModuleInit");
		}
	}
}