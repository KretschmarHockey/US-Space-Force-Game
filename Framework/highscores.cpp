#include "highscores.h"
#include "logmanager.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <fstream>
#include <string>

HighScore::HighScore()
{
	
}


HighScore::~HighScore()
{
	for (size_t i = 0; i < m_scores.size(); i++)
	{
		delete m_scores[i];
		m_scores[i] = 0;
	}
	for (size_t i = 0; i < m_level.size(); i++)
	{
		delete m_level[i];
		m_level[i] = 0;
	}
	for (size_t i = 0; i < m_name.size(); i++)
	{
		delete m_name[i];
		m_name[i] = 0;
	}
}

void
HighScore::AddScore(std::string line)
{
	int* c = new int(std::stoi(line));
	m_scores.push_back(c);
}

void
HighScore::AddLevel(std::string line)
{
	int* c = new int(std::stoi(line));
	m_level.push_back(c);
}

void
HighScore::AddName(std::string line)
{
	std::string* c = new std::string(line);
	m_name.push_back(c);
}

int*
HighScore::GetScore(int index)
{
	return m_scores[index];
}

int*
HighScore::GetLevel(int index)
{
	return m_level[index];
}

std::string*
HighScore::GetName(int index)
{
	return m_name[index];
}

int
HighScore::GetLowestScore()
{
	return *m_scores[9];
}

void
HighScore::SubmitScore(int* p_score, int* p_level, std::string* p_name)
{
	delete m_scores[9];
	m_scores[9] = 0;
	m_scores.pop_back();
	delete m_level[9];
	m_level[9] = 0;
	m_level.pop_back();
	delete m_name[9];
	m_name[9] = 0;
	m_name.pop_back();

	auto it = std::lower_bound(m_scores.begin(), m_scores.end(), p_score, [](const int* a, const int* b) { return *a > *b; });
	int* score = new int(*p_score);
	m_scores.insert(it, score);

	it = std::find(m_scores.begin(), m_scores.end(), score);

	int* level = new int(*p_level);
	m_level.insert(m_level.begin() + std::distance(m_scores.begin(), it), level);

	std::string* name = new std::string(*p_name);
	m_name.insert(m_name.begin() + std::distance(m_scores.begin(), it), name);

	SaveToFile();
}

void
HighScore::SaveToFile()
{
	std::ofstream file;
	file.open("highscore.ini");

	if (file.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			file << *m_scores[i] << std::endl;
			file << *m_level[i] << std::endl;
			file << *m_name[i] << std::endl;
		}
		file.close();
	}
	else
	{
		LogManager::GetInstance().Log("Unable to open file");
	}
}

bool
HighScore::IsEmpty()
{
	return m_name.empty();
}