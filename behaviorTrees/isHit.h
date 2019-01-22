#ifndef __IS_HIT_H__
#define __IS_HIT_H__

#include "behavior.h"

class IsHit : public Behavior {

protected:
	Status update();

public:
	IsHit(GameEntity* entity);
};

#endif