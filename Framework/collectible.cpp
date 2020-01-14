#include "collectible.h"
#include "game.h"
#include <time.h>
#include <math.h>
#include <cstdlib>
#include <cstring>

Collectible::Collectible()
{	
	srand((unsigned int) time(NULL));
}


Collectible::~Collectible()
{
}

void
Collectible::Process(float deltaTime)
{
	m_previousX = m_x;
	m_previousY = m_y;

	if (m_x < 0 || m_x > Game::GetWidth())
	{
		this->Kill();
	}
	
	m_x += deltaTime * m_velocityX;
	
}

void
Collectible::SetRandomType()
{
	m_dead = false;

	// Position
	int direction = rand() % 2;
	if (direction == 0)
	{
		m_x = 0;
		m_velocityX = 200;
	}
	else
	{
		m_x = static_cast <float> (Game::GetWidth());
		m_velocityX = -200;
	}

	float temp = static_cast <float> (rand() % Game::GetHeight());
	m_y = temp;


	// Type
	int type = rand() % 100;

	if (type >= 0 && type <= 32)
	{
		this->type = AMMO;
	}
	else
	{
		this->type = AMMO;
	}
	// TODO: More Collectibles

}

Type
Collectible::GetType()
{
	return this->type;
}

void
Collectible::Kill()
{
	this->m_dead = true;
}