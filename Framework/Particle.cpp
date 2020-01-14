#include "particle.h"
#include "sprite.h"
#include "backbuffer.h"
#include <cassert>

Particle::Particle()
{
}


Particle::~Particle()
{
}

bool
Particle::Initialise(Sprite * sprite)
{
	assert(sprite);
	m_pSprite = sprite;

	return (true);
}

void
Particle::Draw(BackBuffer & backBuffer, int x, int y, SDL_Rect* clip)
{
	assert(m_pSprite);
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));
	m_pSprite->DrawParticle(backBuffer, x, y, clip);
}

void
Particle::Process(float deltatime)
{

}

void
Particle::SetDead(bool dead)
{
	m_dead = dead;
}

bool
Particle::IsDead() const
{
	return m_dead;
}

void
Particle::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}

void
Particle::SetLifeSpan(float lifespan)
{
	m_lifespan = lifespan;
}

float
Particle::GetPositionX() const
{
	return (m_x);
}

float
Particle::GetPositionY() const
{
	return (m_y);
}