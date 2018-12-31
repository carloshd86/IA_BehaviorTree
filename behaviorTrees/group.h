#ifndef __GROUP_H__
#define __GROUP_H__

#include <vector>
#include "behavior.h"

class Group : public Behavior {

public:
	Group(GameEntity* entity, const char* filename);
	~Group();

	void load();

protected:
	typedef std::vector<Behavior*> Behaviors;

	Behaviors   mChildren;
	const char* mFilename;
};

#endif