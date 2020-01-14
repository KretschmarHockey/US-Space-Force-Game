#include "entity.h"
#ifndef __BULLET_H__
#define __BULLET_H__

class Bullet : public Entity
{
public:
	Bullet();
	~Bullet();

	void Process(float deltaTime);

private:
	Bullet(const Bullet& bullet);
	Bullet& operator=(const Bullet& bullet);
};

#endif // __BULLET_H__