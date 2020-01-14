#ifndef __INIPARSER_H__
#define __INIPARSER_H__

#include <string>
#include <map>
#include "highscores.h"

class HighScore;

class IniParser
{
public:
	IniParser();
	~IniParser();

	bool LoadIniFile(const std::string& filename);
	void LoadHighScore(const std::string& filename);
	std::string GetValueAsString(const std::string& iniSection, const std::string& key);
	int GetValueAsInt(const std::string& iniSection, const std::string& key);
	float GetValueAsFloat(const std::string& iniSection, const std::string& key);
	bool GetValueAsBoolean(const std::string& iniSection, const std::string& key);


private:
	std::map<std::string, std::map<std::string, std::string>> sections;
};


#endif // __INIPARSER_H__