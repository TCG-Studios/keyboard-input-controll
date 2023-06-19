#pragma once


#include <functional>
#include <string>
#include <filesystem>
#include <assert.h>


#include "iWin.h"

namespace modules {

	const enum class Flag : uint8_t
	{
		None = 0,
		Loaded = 1 << 0,
		AliasSet = 1 << 1,
		NeedsInitialization = 1 << 2,
		NeedsCleanup = 1 << 3,
		// Add more flags as needed
	};

	Flag operator|(Flag lhs, Flag rhs);

	Flag operator&(Flag lhs, Flag rhs);

	Flag operator^(Flag lhs, Flag rhs);

	bool operator==(Flag lhs, Flag rhs);

	bool operator!=(Flag lhs, Flag rhs);

	Flag operator~(Flag lhs);

	Flag createFlag(uint8_t value);

	bool hasFlag(Flag flag, const Flag checkFlag);

	void setFlag(Flag& flag, Flag setFlag);

	void clearFlag(Flag& flag, const Flag clearFlag);
}

namespace fs = std::filesystem;

class Module
{
	/***** Con-/Destructor *****/
public:
	Module(const std::string& libPath, const std::string& alias = "")
		: s_libPath(libPath), s_alias(alias)
	{
		m_flag = modules::Flag::None;
	}

	Module(const fs::path& libPath, const std::string& alias = "")
		: Module(libPath.string(), alias) { }

	~Module()
	{ freeLibrary(); }

	bool loadLibrary();

	bool freeLibrary();

	bool reloadLibrary();

	std::string getAlias() const { return s_alias; }

	bool isLoaded() const
	{ return modules::hasFlag(m_flag, modules::Flag::Loaded); }

	bool hasAlias() const
	{ return modules::hasFlag(m_flag, modules::Flag::AliasSet); }

	bool requiresInitialization() const
	{ return modules::hasFlag(m_flag, modules::Flag::NeedsInitialization); }

	bool requiresCleanup() const
	{ return modules::hasFlag(m_flag, modules::Flag::NeedsCleanup); }

	const std::string& getPath() const 
	{ return s_libPath; }
private:
	template <typename T>
	std::function<void()> getFunction(const char* functionName);
protected:


	/***** Members *****/
public:
	std::unordered_map<std::string, u64> p_functionNames;
	std::vector<std::function<void()>*> p_functionPtrs;
private:
	modules::Flag m_flag = modules::createFlag(0);
	HMODULE h_Module = nullptr;  // Handle to the DLL
	std::string s_libPath; // Path of the DLL
	std::string s_alias; // Alias of the library
	
	
	std::unordered_map<std::string, u64> p_functionNames;
	std::vector<std::function<void()>*> p_functionPtrs;
};

namespace modules {
	std::vector<Module*> selectedModules;
	void LoadAllSelectedModules();
	void freeAllSelectedModules();
	void initAllSelectedModules();
}