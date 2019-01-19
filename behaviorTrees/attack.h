#ifndef __ATTACK_H__
#define __ATTACK_H__

#include "behavior.h"

class Attack : public Behavior {

protected:
	Status update();

public:
	Attack(GameEntity* entity, int damage = 0);

private:
	int mDamage;
};

#endif