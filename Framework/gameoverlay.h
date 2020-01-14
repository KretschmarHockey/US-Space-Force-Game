#ifndef __OVERLAY_H__
#define __OVERLAY_H__

#include <SDL.h>
#include <SDL_ttf.h>

class BackBuffer;

class Overlay
{
public:
	Overlay();
	~Overlay();

	void Draw(BackBuffer& backBuffer);

	void AddScore(int score);
	void SetScore(int score);
	int GetScore();

	void LevelUp();
	void SetLevel(int level);
	int GetLevel();
	void SetLives(int lives);
	void SetBullets(int bullets);

protected:
	int m_iScore;
	int m_iLevel;
	int m_iLives;
	int m_iBullets;
};

#endif // __OVERLAY_H__