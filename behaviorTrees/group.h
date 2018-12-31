#ifndef __GROUP_H__
#define __GROUP_H__

#include "behavior.h"
#include <vector>

class Group : public Behavior {

protected:
	typedef std::vector<Behavior*> Behaviors;

	Behaviors mChildren;
};

#endif