#ifndef __IDLE_H__
#define __IDLE_H__

#include "behavior.h"

class Idle : public Behavior {

protected:
	Status update();
	void   onEnter();
	void   onExit();

public:
	Idle(GameEntity* entity);
};

#endif