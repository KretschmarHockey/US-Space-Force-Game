#include "entity.h"
#ifndef __PLAYERSHIP_H__
#define __PLAYERSHIP_H__ 

enum Direction { LEFT, RIGHT };

class Playership : public Entity
{
	// Methods
public:
	Playership();
	~Playership();

	void Process(float deltaTime);
	virtual void Draw(BackBuffer& backBuffer);

	void SetDirection(Direction direction);
	Direction GetDirection();

	void SetInvincibility(bool invincible);
	bool IsInvincible();
	void SetInvincibleTimer(float timer);

	float m_fInvincibilityTimer;

private:
	Playership(const Playership& playership);
	Playership& operator=(const Playership& playership);

	// Members

protected:
	Direction m_dDirection;
	bool m_bInvincibility;
};

#endif // __PLAYERSHIP_H__
