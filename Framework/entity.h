// COMP710 GP 2D Framework 2019
#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <SDL.h>

// Forward Declarations:
class BackBuffer;
class Sprite;
class AnimatedSprite;

class Entity
{
	static int instance;
public:

	//Member Methods:
public:
	Entity();
	~Entity();

	bool Initialise(Sprite* sprite);
	bool Initialise(AnimatedSprite* sprite);

	void Draw(BackBuffer& backBuffer);
	void Animate(BackBuffer& backBuffer);

	void SetDead(bool dead);
	bool IsDead() const;

	bool IsCollidingWith(Entity& e);

	void SetPosition(float x, float y);
	void SetPositionX(float x);
	void SetPositionY(float y);

	float GetPositionX() const;
	float GetPositionY() const;

	float GetHorizontalVelocity() const;
	void SetHorizontalVelocity(float x); 

	float GetVerticalVelocity() const;
	void SetVerticalVelocity(float y);

	Sprite* GetSprite();
	AnimatedSprite* GetAnimatedSprite();

protected:

private:
	Entity(const Entity& entity);
	Entity& operator=(const Entity& entity);

	//Member Data:
public:

protected:
	Sprite* m_pSprite;
	AnimatedSprite* m_pAnimatedSprite;

	float m_x;
	float m_y;

	float m_previousX;
	float m_previousY;

	float m_velocityX;
	float m_velocityY;

	bool m_dead;

private:

};

#endif //__ENTITY_H__
