#include "entity.h"
#ifndef __ENEMY_H__
#define __ENEMY_H__


class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();

	void Process(float deltaTime);

	float startPosX;
	float startPosY;
	float endPosX;
	float endPosY;
	float distanceToTravelX;
	float distanceToTravelY;
	float distanceTraveledSoFarX;
	float distanceTraveledSoFarY;
	bool xMoving = false;
	bool yMoving = false;

private:
	Enemy(const Enemy& enemy);
	Enemy& operator=(const Enemy& enemy);
};

#endif // __ENEMY_H__