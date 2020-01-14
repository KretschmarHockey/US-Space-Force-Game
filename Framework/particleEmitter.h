#ifndef __PARTICLEEMITTER_H__
#define __PARTICLEEMITTER_H__

#include <vector>
#include <SDL.h>
#include "particle.h"
#include "debris.h"

class Sprite;

class ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();

	bool Initialise(Sprite* m_pSpriteSheet);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void AddParticle(int numberOfParticles, float x, float y);
	bool HasParticles();

	void SetFrameWidth(int w);
	void DivideSpriteSheet(int x);

	void KillParticles();

protected:
	std::vector<Particle*> m_vParticles;

	SDL_Rect m_SpriteClips[8];

	Sprite* m_pSpriteSheet;

	int m_frameWidth;
};

#endif // __PARTICLEEMITTER_H_