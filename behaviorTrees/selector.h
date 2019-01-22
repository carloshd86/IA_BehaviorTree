#ifndef __SELECTOR_H__
#define __SELECTOR_H__

#include "group.h"

class Selector : public Group {

public:
	Selector(GameEntity* entity);

protected:
	void   onEnter();
	Status update();
	void   onExit();

	int mCurrentChild;
};

#endif