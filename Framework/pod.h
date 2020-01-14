#include "entity.h"
#ifndef __POD_H__
#define __POD_H__

class Pod : public Entity
{
public:
	Pod();
	~Pod();

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
	Pod(const Pod& pod);
	Pod& operator=(const Pod& pod);
};


#endif // __POD_H__
