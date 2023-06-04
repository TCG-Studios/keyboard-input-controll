#pragma once

#include "parser_base.h"

#include <string>
#include <unordered_map>

class IniParser : public Parser_base {
public:
	IniParser(bool caseSensitive = false) : caseSensitive(caseSensitive) {}

	uint8_t read(const std::string& filename) override {
		if (!checkDir(filename))
		{
			return 1;
		}
		std::ifstream file(filename);
		if (!file) {
			throw std::runtime_error("Failed to open file: " + filename);
		}

		std::string line;
		std::string currentSection;
		while (std::getline(file, line)) {
			line = removeComment(line);
			if (line.empty()) {
				continue;
			}

			if (isSection(line)) {
				currentSection = getSectionName(line);
				if (!caseSensitive) {
					currentSection = toLower(currentSection);
				}
				if (sections.count(currentSection) > 0) {
					throw std::runtime_error("Duplicate section: " + currentSection);
				}
				sections[currentSection] = {};
			}
			else {
				std::string key, value;
				if (!parseLine(line, key, value)) {
					throw std::runtime_error("Invalid line: " + line);
				}
				if (!caseSensitive) {
					key = toLower(key);
				}
				sections[currentSection][key] = value;
			}
		}
	}

	uint8_t write(const std::string& filename) override {
		if (!checkDir(filename))
		{
			int re = createDir(filename);
			if (!checkDir(filename))
				return re;
		}
		std::ofstream file(filename);
		if (!file) {
			throw std::runtime_error("Failed to open file: " + filename);
		}
		for (const auto& section : sections) {
			file << "[" << section.first << "]" << std::endl;
			for (const auto& keyValuePair : section.second) {
				file << keyValuePair.first << " = " << keyValuePair.second << std::endl;
			}
			file << std::endl;
		}
	}

	void merge(const IniParser& other, bool overwrite = true) {
		for (const auto& otherSection : other.sections) {
			if (sections.count(otherSection.first) == 0) {
				sections[otherSection.first] = otherSection.second;
			}
			else {
				auto& section = sections[otherSection.first];
				for (const auto& otherKeyValuePair : otherSection.second) {
					if (section.count(otherKeyValuePair.first) == 0 || overwrite) {
						section[otherKeyValuePair.first] = otherKeyValuePair.second;
					}
				}
			}
		}
	}

	void validate() const {
		for (const auto& section : sections) {
			for (const auto& keyValuePair : section.second) {
				if (keyValuePair.first.empty() || keyValuePair.second.empty()) {
					throw std::runtime_error("Empty key or value in section " + section.first);
				}
			}
		}
	}

	template<typename T>
	T get(const std::string& section, const std::string& key, const T& defaultValue) const {
		if (sections.count(section) == 0) {
			return defaultValue;
		}
		const auto& sectionData = sections.at(section);
		if (sectionData.count(key) == 0) {
			return defaultValue;
		}
		return convert<T>(sectionData.at(key));
	}

	template<typename T>
	T get(const std::string& section, const std::string& key) const {
		if (sections.count(section) == 0) {
			throw std::runtime_error("Section not found: " + section);
		}
		const auto& sectionData = sections.at(section);
		if (sectionData.count(key) == 0) {
			throw std::runtime_error("Key not found: " + key);
		}
		return convert<T>(sectionData.at(key));
	}

	void set(const std::string& section, const std::string& key, const std::string& value) {
		if (!caseSensitive) {
			sections[toLower(section)][toLower(key)] = value;
		}
		else {
			sections[section][key] = value;
		}
	}

	std::string getParsingType() override {
		return "ini";
	}
	
private:
	bool caseSensitive;
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> sections;
	
	
	std::string removeComment(const std::string& line) const {
		const auto commentPos = line.find('#');
		if (commentPos != std::string::npos) {
			return line.substr(0, commentPos);
		}
		return line;
	}
	
	bool isSection(const std::string& line) const {
		return line.front() == '[' && line.back() == ']';
	}
	
	std::string getSectionName(const std::string& line) const {
		return line.substr(1, line.size() - 2);
	}
	
	bool parseLine(const std::string& line, std::string& key, std::string& value) const {
		const auto equalsPos = line.find('=');
		if (equalsPos == std::string::npos) {
			return false;
		}
		key = line.substr(0, equalsPos);
		value = line.substr(equalsPos + 1);
		key = trim(key);
		value = trim(value);
		return !key.empty();
	}
	
	std::string trim(const std::string& str) const {
		const auto start = str.find_first_not_of(" \t");
		const auto end = str.find_last_not_of(" \t");
		if (start == std::string::npos || end == std::string::npos) {
			return "";
		}
		return str.substr(start, end - start + 1);
	}
	
	std::string toLower(std::string str) const {
		std::transform(str.begin(), str.end(), str.begin(), [](char c) { return std::tolower(c); });
		return str;
	}
	
	template<typename T>
	T convert(const std::string& str) const {
		std::istringstream iss(str);
		T result = {};
		if (!(iss >> result)) {
			throw std::runtime_error("Failed to convert string to value: " + str);
		}
		return result;
	}
};