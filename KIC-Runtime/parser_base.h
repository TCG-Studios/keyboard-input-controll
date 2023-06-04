#pragma once

#include <fstream>
#include <filesystem>
#include <assert.h>

namespace fs = std::filesystem;

class Parser_base {
public:
	Parser_base() {}
	virtual ~Parser_base() {}

	virtual uint8_t read(const std::string& filename) = 0;
	virtual uint8_t write(const std::string& filename) = 0;

	static bool checkDir(const std::string& filename)
	{
		return fs::exists(filename);
	}

	static uint8_t deleteDir(const std::string& filename)
	{
		int re = fs::remove(filename);
		if (checkDir(filename))
			return re;
		else
			return 0;
	}

	static uint8_t createDir(const std::string& filename, bool ignoreExist = false)
	{
		if (checkDir(filename) && !ignoreExist)
			return 1;
		else
		{
			std::ofstream creater(filename, std::ios::trunc | std::ios::out);
			if (!creater.is_open())
			{
				creater.close();
				return deleteDir(filename);
			}
			else
			{
				creater.close();
				return 0;
			}
		}
	}

private:
	virtual std::string getParsingType() = 0;
};
