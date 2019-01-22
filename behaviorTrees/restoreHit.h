#ifndef __RESTORE_HIT_H__
#define __RESTORE_HIT_H__

#include "behavior.h"

class RestoreHit : public Behavior {

protected:
	Status update();
	void   onExit();

public:
	RestoreHit(GameEntity* entity);
};

#endif