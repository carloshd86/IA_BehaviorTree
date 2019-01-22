#ifndef __PURSUE_H__
#define __PURSUE_H__

#include "behavior.h"

class Pursue : public Behavior {

protected:
	Status update();
	void   onEnter();
	void   onExit();

public:
	Pursue(GameEntity* entity);

private:
	bool mInitialized;
};

#endif