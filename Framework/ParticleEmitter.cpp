#include "particleEmitter.h"

#include "debris.h"
#include "sprite.h"

#include <cassert>

ParticleEmitter::ParticleEmitter()
{
}


ParticleEmitter::~ParticleEmitter()
{
	for (size_t i = 0; i < m_vParticles.size(); ++i)
	{
		delete m_vParticles[i];
		m_vParticles[i] = 0;
	}
	delete m_pSpriteSheet;
	m_pSpriteSheet = 0;
}

bool
ParticleEmitter::Initialise(Sprite* spriteSheet)
{
	assert(m_pSpriteSheet);
	m_pSpriteSheet = spriteSheet;

	return (true);
}

void
ParticleEmitter::Process(float deltaTime)
{
	for (auto pParticle = m_vParticles.begin(); pParticle != m_vParticles.end();)
	{
		(*pParticle)->Process(deltaTime);
		
		if ((*pParticle)->IsDead())
		{
			delete *pParticle;
			pParticle = m_vParticles.erase(pParticle);
		}
		else
		{
			++pParticle;
		}
	}
}

void
ParticleEmitter::Draw(BackBuffer& backBuffer)
{
	for (size_t i = 0; i < m_vParticles.size(); i++)
	{
		SDL_Rect* cell = &m_SpriteClips[rand() % 8];
		m_vParticles[i]->Draw(backBuffer, static_cast <int> (m_vParticles[i]->GetPositionX()), static_cast <int> (m_vParticles[i]->GetPositionY()), cell);
	}
}

void
ParticleEmitter::DivideSpriteSheet(int x)
{
	for (int i = 0; i < x; i++)
	{
		m_SpriteClips[i].x = (m_frameWidth * i) % 64;
		if (i < 4)
		{
			m_SpriteClips[i].y = 0;
		}
		else
		{
			m_SpriteClips[i].y = 8;
		}
		m_SpriteClips[i].w = m_frameWidth;
		m_SpriteClips[i].h = m_frameWidth;
	}
}

void
ParticleEmitter::AddParticle(int numberOfParticles, float x, float y)
{
	for (int i = 0; i < numberOfParticles; i++)
	{
		Debris* debris = new Debris();
		debris->Initialise(m_pSpriteSheet);
		debris->Generate();
		debris->SetPosition(x, y);
		debris->SetDead(false);
		m_vParticles.push_back(debris);
	}
}

bool
ParticleEmitter::HasParticles()
{
	return m_vParticles.size() > 0;
}

void
ParticleEmitter::SetFrameWidth(int w)
{
	m_frameWidth = w;
}

void
ParticleEmitter::KillParticles()
{
	for (auto pParticle = m_vParticles.begin(); pParticle != m_vParticles.end();)
	{
		delete *pParticle;
		pParticle = m_vParticles.erase(pParticle);
	}
}