#ifndef __HIGHSCORE_H__
#define __HIGHSCORE_H__

#include <string>
#include <vector>

class HighScore
{
public:
	HighScore();
	~HighScore();

	void AddScore(std::string line);
	void AddLevel(std::string line);
	void AddName(std::string line);

	int* GetScore(int index);
	int* GetLevel(int index);
	std::string* GetName(int index);

	int GetLowestScore();
	void SubmitScore(int* score, int* level, std::string* name);
	bool IsEmpty();
	void SaveToFile();

protected:
	std::vector<int*> m_scores;
	std::vector<int*> m_level;
	std::vector<std::string*> m_name;
};

#endif // __HIGHSCORE_H__