#ifndef __SELECTOR_H__
#define __SELECTOR_H__

#include "group.h"

class Selector : public Group {

protected:
	void   onEnter();
	Status update();

	int mCurrentChild;
};

#endif