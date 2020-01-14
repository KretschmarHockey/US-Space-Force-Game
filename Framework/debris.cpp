#include "debris.h"
#include <cstdlib>
#include <time.h>
#include <math.h>


Debris::Debris()
{
}


Debris::~Debris()
{
}

void
Debris::Process(float deltaTime)
{
	m_lifespan -= deltaTime;
	m_x += m_velocityX;
	m_y += m_velocityY;
	if (m_lifespan < 0)
	{
		m_dead = true;
	}
}

void
Debris::Generate()
{
	m_lifespan = static_cast <float> (rand() % 10);
	m_velocityX = (rand() % 10) - 5.0f;
	m_velocityY = (rand() % 10) - 5.0f;
}