#ifndef __COLLECTIBLE_H__
#define __COLLECTIBLE_H__

#include "entity.h"

enum Type { AMMO, PLUS50, INVINCIBILITY, POWERBULLET, CONTROLLEDBULLET, LIFE };

class Collectible : public Entity
{
public:
	Collectible();
	~Collectible();

	void Process(float deltaTime);
	void SetRandomType();
	Type GetType();
	void Kill();

protected:
	Type type;
};

#endif // __COLLECTIBLE_H__