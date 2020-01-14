#include "bullet.h"
#include "sprite.h"
#include "game.h"

#include <cstring>

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

void
Bullet::Process(float deltaTime)
{
	m_previousX = m_x;
	m_previousY = m_y;

	int widthBound = Game::GetInstance().GetWidth();

	if (m_x < 0 || m_x + (m_pSprite->GetWidth()) > widthBound)
	{
		SetDead(true);
	}

	m_x = (m_x + m_velocityX * deltaTime);
}


