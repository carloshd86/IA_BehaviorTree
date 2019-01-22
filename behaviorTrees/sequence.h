#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__

#include "group.h"

class Sequence : public Group {

public:
	Sequence(GameEntity* entity);

protected:
	void   onEnter();
	Status update();
	void   onExit();

	int mCurrentChild;
};

#endif