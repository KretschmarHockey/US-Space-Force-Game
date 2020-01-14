#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include <SDL.h>

class BackBuffer;
class Sprite;

class Particle
{
public:
	Particle();
	~Particle();

	virtual void Process(float deltaTime);

	bool Initialise(Sprite* sprite);
	
	void Draw(BackBuffer& backBuffer, int x, int y, SDL_Rect* clip);

	void SetDead(bool dead);
	bool IsDead() const;

	void SetLifeSpan(float lifespan);

	void SetPosition(float x, float y);
	float GetPositionX() const;
	float GetPositionY() const;
	
protected:
	Sprite* m_pSprite;

	float m_x;
	float m_y;

	float m_velocityX;
	float m_velocityY;

	float m_lifespan;

	bool m_dead;

};

#endif // __PARTICLE_H__