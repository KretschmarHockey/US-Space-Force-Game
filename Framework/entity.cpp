// COMP710 GP 2D Framework 2019

// This include:
#include "entity.h"

// Local includes:
#include "sprite.h"
#include "animatedSprite.h"
#include "backbuffer.h"


// Library includes:
#include <cassert>
#include <cstdio>
#include <SDL.h>


Entity::Entity()
: m_pSprite(0)
, m_x(0.0f)
, m_y(0.0f)
, m_velocityX(0.0f)
, m_velocityY(0.0f)
, m_dead(false)
{
}

Entity::~Entity()
{
}

bool
Entity::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;

	return (true);
}

bool
Entity::Initialise(AnimatedSprite* sprite)
{
	assert(sprite);
	m_pAnimatedSprite = sprite;

	return (true);
}

void 
Entity::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));
	m_pSprite->Draw(backBuffer);
	
}

void
Entity::Animate(BackBuffer& backBuffer)
{
	assert(m_pAnimatedSprite);
	m_pAnimatedSprite->SetX(static_cast<int>(m_x));
	m_pAnimatedSprite->SetY(static_cast<int>(m_y));
	m_pAnimatedSprite->Draw(backBuffer);
}

bool
Entity::IsCollidingWith(Entity& e)
{
	return !(e.m_x > m_x + m_pSprite->GetWidth()
		|| e.m_x + e.GetSprite()->GetWidth() < m_x
		|| e.m_y > m_y + m_pSprite->GetHeight()
		|| e.m_y + e.GetSprite()->GetHeight() < m_y);
}

void 
Entity::SetDead(bool dead)
{
	m_dead = dead;
}

void
Entity::SetPosition(float x, float y)
{
	m_x = x;
	m_previousX = x;
	m_y = y;
	m_previousY = y;
}

void
Entity::SetPositionX(float x)
{
	m_x = x;
	m_previousX = x;
}

void
Entity::SetPositionY(float y)
{
	m_y = y;
	m_previousY = y;
}

float 
Entity::GetPositionX() const
{
	return (m_x);
}

float 
Entity::GetPositionY() const
{
	return (m_y);
}

float 
Entity::GetHorizontalVelocity() const
{
	return (m_velocityX);
}

float 
Entity::GetVerticalVelocity() const
{
	return (m_velocityY);
}

void 
Entity::SetHorizontalVelocity(float x)
{
	m_velocityX = x;
}

void 
Entity::SetVerticalVelocity(float y)
{
	m_velocityY = y;
}

Sprite*
Entity::GetSprite()
{
	return m_pSprite;
}

AnimatedSprite*
Entity::GetAnimatedSprite()
{
	return m_pAnimatedSprite;
}

bool
Entity::IsDead() const
{
	return m_dead;
}