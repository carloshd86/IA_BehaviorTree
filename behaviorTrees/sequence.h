#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__

#include "group.h"

class Sequence : public Group {

protected:
	void   onEnter();
	Status update();

	int mCurrentChild;
};

#endif