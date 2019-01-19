#ifndef __ENEMY_CLOSE_H__
#define __ENEMY_CLOSE_H__

#include "behavior.h"

class EnemyClose : public Behavior {

protected:
	Status update();

public:
	EnemyClose(GameEntity* entity, float minDistance);

private:
	float mMinDistance;
};

#endif