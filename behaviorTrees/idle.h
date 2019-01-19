#ifndef __IDLE_H__
#define __IDLE_H__

#include "behavior.h"

class Idle : public Behavior {

protected:
	Status update();

public:
	Idle(GameEntity* entity, float radius = 0.f, bool reverse = false, float speed = 0.f);

private:
	float mRadius;
	bool  mReverse;
	float mSpeed;
};

#endif