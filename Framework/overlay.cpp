#include "gameoverlay.h"
#include "game.h"
#include "backbuffer.h"
#include <array>
#include <string>
#include <stdio.h>

Overlay::Overlay()
{
}


Overlay::~Overlay()
{
}

void
Overlay::Draw(BackBuffer& backBuffer)
{
	int widthBound = Game::GetWidth();
	int heightBound = Game::GetHeight();

		
		backBuffer.SetDrawColour(200, 200, 200);
		backBuffer.DrawRectangle(0, heightBound, widthBound, heightBound + 50);
		// Score
		backBuffer.SetTextColour(0, 0, 0);
		backBuffer.DrawText(10, heightBound, "Score:");
		backBuffer.SetTextColour(0, 0, 200);
		char score[10];
		snprintf(score, 10, "%d", m_iScore);
		backBuffer.DrawText(170, heightBound, score);

		// Level
		backBuffer.SetTextColour(0, 0, 0);
		backBuffer.DrawText(380, heightBound, "Level:");
		backBuffer.SetTextColour(200, 0, 200);
		char level[3];
		snprintf(level, 3, "%d", m_iLevel);
		backBuffer.DrawText(540, heightBound, level);

		// Lives
		backBuffer.SetTextColour(0, 0, 0);
		backBuffer.DrawText(750, heightBound, "Lives:");
		backBuffer.SetTextColour(200, 0, 0);
		char lives[3];
		snprintf(lives, 3, "%d", m_iLives);
		backBuffer.DrawText(910, heightBound, lives);

		// Bullets
		backBuffer.SetTextColour(0, 0, 0);
		backBuffer.DrawText(1120, heightBound, "Bullets:");
		backBuffer.SetTextColour(0, 200, 0);
		char bullets[3];
		snprintf(bullets, 3, "%d", m_iBullets);
		backBuffer.DrawText(1310, heightBound, bullets);
}

void
Overlay::AddScore(int score)
{
	this->m_iScore += score;
}

void
Overlay::SetScore(int score)
{
	this->m_iScore = score;
}

int
Overlay::GetScore()
{
	return this->m_iScore;
}

void
Overlay::LevelUp()
{
	this->m_iLevel++;
}

void
Overlay::SetLevel(int level)
{
	this->m_iLevel = level;
}

int
Overlay::GetLevel()
{
	return this->m_iLevel;
}

void
Overlay::SetLives(int lives)
{
	this->m_iLives = lives;
}

void
Overlay::SetBullets(int bullets)
{
	this->m_iBullets = bullets;
}