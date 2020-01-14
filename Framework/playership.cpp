#include "playership.h"
#include <cassert>

#include "sprite.h"
#include "game.h"
#include <cstdio>

Playership::Playership()
	: m_bInvincibility(false)
{
}


Playership::~Playership()
{
}


void
Playership::Process(float deltaTime)
{

	m_previousX = m_x;
	m_previousY = m_y;

	int widthBound = Game::GetWidth();
	int heightBound = Game::GetHeight();

	m_x += (m_velocityX * deltaTime);
	m_y += (m_velocityY * deltaTime);

	if (m_x > widthBound - m_pSprite->GetWidth())
	{
		m_x = widthBound - static_cast <float> (m_pSprite->GetWidth());
	}
	if (m_x < 0)
	{
		m_x = 0;
	}

	if (m_y > (heightBound) - m_pSprite->GetHeight())
	{
		m_y = static_cast <float> ((heightBound) - m_pSprite->GetHeight());
	}
	if (m_y < 0)
	{
		m_y = 0;
	}
}

void
Playership::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));
	m_pSprite->DrawFlippableSprite(backBuffer, m_dDirection);

}

void
Playership::SetDirection(Direction direction)
{
	this->m_dDirection = direction;
}

Direction
Playership::GetDirection()
{
	return this->m_dDirection;
}

void
Playership::SetInvincibility(bool invincible)
{
	this->m_bInvincibility = invincible;
}

bool
Playership::IsInvincible()
{
	return this->m_bInvincibility;
}

void
Playership::SetInvincibleTimer(float timer)
{
	m_fInvincibilityTimer = timer;

}