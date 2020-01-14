#ifndef __DEBRIS_H__
#define __DEBRIS_H__

#include "particle.h"

class Debris : public Particle
{
public:
	Debris();
	~Debris();

	virtual void Process(float deltaTime);

	void Generate();
};

#endif // __DEBRIS_H__