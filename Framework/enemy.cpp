#include "enemy.h"
#include "game.h"
#include "sprite.h"
#include "iniParser.h"
#include <time.h>
#include <math.h>
#include <cstring>

Enemy::Enemy()
{	
	srand((unsigned int) time(NULL));
}


Enemy::~Enemy()
{
}

void
Enemy::Process(float deltaTime)
{
	m_previousX = m_x;
	m_previousY = m_y;

	int speed = Game::GetInstance().GetIniParser()->GetValueAsInt("enemy", "speed");
	int range = Game::GetInstance().GetIniParser()->GetValueAsInt("enemy", "speedRange");

	if (!xMoving && !yMoving)
	{
		endPosX = static_cast <float> (rand() % (Game::GetWidth() - GetSprite()->GetWidth()));
		endPosY = static_cast <float> (rand() % (Game::GetHeight() - GetSprite()->GetHeight()));
		m_velocityX = static_cast <float> (rand() % range + speed);
		m_velocityY = static_cast <float> (rand() % range + speed);
		xMoving = true;
		yMoving = true;
		startPosX = m_x;
		startPosY = m_y;
		distanceToTravelX = abs(startPosX - endPosX);
		distanceToTravelY = abs(startPosY - endPosY);
		distanceTraveledSoFarX = 0;
		distanceTraveledSoFarY = 0;
	}
	else
	{
		distanceTraveledSoFarX = abs(startPosX - m_x);
		distanceTraveledSoFarY = abs(startPosY - m_y);
		if (distanceTraveledSoFarY >= distanceToTravelY)
		{
			yMoving = false;
		}
		else
		{
			if (startPosY < endPosY)
			{
				m_y += deltaTime * m_velocityY;
			}
			else
			{
				m_y -= deltaTime * m_velocityY;
			}
		}

		if (distanceTraveledSoFarX >= distanceToTravelX)
		{
			xMoving = false;
		}
		else
		{
			if (startPosX < endPosX)
			{
				m_x += deltaTime * m_velocityX;
			}
			else
			{
				m_x -= deltaTime * m_velocityX;
			}
		}
	}
}