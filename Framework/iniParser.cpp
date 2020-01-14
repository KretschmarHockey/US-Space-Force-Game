#include "iniParser.h"
#include "logmanager.h"
#include "game.h"

#include <fstream>
#include "highscores.h"

IniParser::IniParser()
{
}


IniParser::~IniParser()
{
}

bool
IniParser::LoadIniFile(const std::string& filename)
{
	std::ifstream is;
	is.open(filename.c_str());
	if (!is.is_open())
	{
		LogManager::GetInstance().Log("Unable to read .ini file");
	}
	
	std::string section = "";
	std::string line;

  	while (getline(is, line))
	{
		if (line == "") {}
		else if (line.at(0) == '[')
		{
			section = line.substr(1, line.size() - 2);
			std::map<std::string, std::string> emptyMap;
			sections[section] = emptyMap;
		}
		else
		{
			std::string optionName = line.substr(0, line.find_first_of("=") - 1);
			std::string optionValue = line.substr(line.find_first_of("=") + 2);
			
			std::map<std::string, std::string>& options = sections[section];
			options[optionName] = optionValue;
		}
	}
	is.close();
	return (true);
}

void
IniParser::LoadHighScore(const std::string& filename)
{
	std::ifstream is;
	is.open(filename.c_str());
	if (!is.is_open())
	{
		LogManager::GetInstance().Log("Unable to read .ini file");
	}

	std::string section = "";
	std::string line;
	int i = 0;

	while (getline(is, line))
	{
		switch (i % 3)
		{
		case 0:
			Game::GetInstance().GetHighScoreBoard()->AddScore(line);
			break;
		case 1:
			Game::GetInstance().GetHighScoreBoard()->AddLevel(line);
			break;
		case 2:
			Game::GetInstance().GetHighScoreBoard()->AddName(line);
			break;
		default:
			break;
		}
		i++;
	}

	is.close();
}

std::string IniParser::GetValueAsString(const std::string & iniSection, const std::string & key)
{
	return sections[iniSection][key];
}

int IniParser::GetValueAsInt(const std::string & iniSection, const std::string & key)
{
	return std::stoi(sections[iniSection][key]);
}

float
IniParser::GetValueAsFloat(const std::string& iniSection, const std::string& key)
{
	return std::stof(sections[iniSection][key]);
}
