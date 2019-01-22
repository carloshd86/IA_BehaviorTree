#ifndef __ENTITY_DEAD_H__
#define __ENTITY_DEAD_H__

#include "behavior.h"

class EntityDead : public Behavior {

protected:
	Status update();

public:
	EntityDead(GameEntity* entity);
};

#endif