#ifndef __PURSUE_H__
#define __PURSUE_H__

#include "behavior.h"

class Pursue : public Behavior {

protected:
	Status update();

public:
	Pursue(GameEntity* entity);
};

#endif