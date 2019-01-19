#ifndef __GROUP_H__
#define __GROUP_H__

#include <vector>
#include "behavior.h"

class Group : public Behavior {

public:
	Group(GameEntity* entity);
	virtual ~Group();

	void load(TiXmlElement* groupElem);

protected:
	typedef std::vector<Behavior*> Behaviors;

	std::vector<Behavior*> mChildren;
};

#endif