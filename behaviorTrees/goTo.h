#ifndef __GO_TO_H__
#define __GO_TO_H__

#include "behavior.h"
#include <uslscore/USVec3D.h>

class GoTo : public Behavior {

protected:
	Status update();
	void   onEnter();
	void   onExit();

public:
	GoTo(GameEntity* entity, USVec3D destination);

private:
	USVec3D mDestination;
};

#endif