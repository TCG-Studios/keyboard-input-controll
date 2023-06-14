#pragma once

#include "iWin.h"
#include <functional>
#include <string>
#include <filesystem>
#include <assert.h>

namespace fs = std::filesystem;

template <typename T>
using fncptr = void(__stdcall*)(T*);

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

	Flag operator|(Flag lhs, Flag rhs) {
		return static_cast<Flag>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
	}

	Flag operator&(Flag lhs, Flag rhs) {
		return static_cast<Flag>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
	}

	Flag operator^(Flag lhs, Flag rhs) {
		return static_cast<Flag>(static_cast<uint8_t>(lhs) ^ static_cast<uint8_t>(rhs));
	}

	bool operator==(Flag lhs, Flag rhs) {
		return static_cast<uint8_t>(lhs) == static_cast<uint8_t>(rhs);
	}

	bool operator!=(Flag lhs, Flag rhs) {
		return static_cast<uint8_t>(lhs) != static_cast<uint8_t>(rhs);
	}

	Flag operator~(Flag lhs) {
		return static_cast<Flag>(~static_cast<uint8_t>(lhs));
	}

	Flag createFlag(uint8_t value) {
		return static_cast<Flag>(value);
	}

	bool hasFlag(Flag flag,const Flag checkFlag) {
		return (flag & checkFlag) == checkFlag;
	}

	void setFlag(Flag& flag, Flag setFlag) {
		flag = flag | setFlag;
	}

	void clearFlag(Flag& flag,const Flag clearFlag) {
		flag = flag & ~clearFlag;
	}
}

class Module
{
	/***** Con-/Destructor *****/
public:
	Module(const std::string& libPath, const std::string& alias = "")
		: s_libPath(libPath), s_alias(alias)
	{
		h_Module = nullptr;
		m_flag = modules::Flag::None;
	}

	Module(const fs::path& libPath, const std::string& alias = "")
		: Module(libPath.string(), alias) { }

	~Module()
	{ freeLibrary(); }

	bool loadLibrary();

	bool freeLibrary();

	bool reloadLibrary();

	template <typename T>
	fncptr<T> getFunction(const char* functionName);

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

protected:


	/***** Members *****/
public:

private:
	modules::Flag m_flag = modules::createFlag(0);
protected:
	HMODULE h_Module;  // Handle to the DLL
	std::string s_libPath; // Path of the DLL
	std::string s_alias; // Alias of the library

};

namespace modules {
	std::vector<Module*> selectedModules;
	void LoadAllSelectedModules() {
		for (const auto sm : selectedModules)
		{
			if (!sm->isLoaded())
				sm->loadLibrary();
		}
	}
	void freeAllSelectedModules() {
		for (const auto sm : selectedModules)
		{
			if (sm->isLoaded())
				sm->freeLibrary();
		}
	}
	void initAllSelectedModules() {
		for (const auto sm : selectedModules)
		{
			if (sm->isLoaded())
			{
				auto initFnc = sm->getFunction<int>("ModuleInit");
			}
		}
	}
}