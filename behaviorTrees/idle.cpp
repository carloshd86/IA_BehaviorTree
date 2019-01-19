#include <stdafx.h>
#include "idle.h"
#include "gameEntity.h"
#include "character.h"
#include "enemy.h"

Idle::Idle(GameEntity* entity, float radius, bool reverse, float speed) :
	Behavior (entity),
	mRadius  (radius),
    mReverse (reverse),
    mSpeed   (speed) {}

Idle::Status Idle::update() {
	Status result = eFail;

	Character* character = static_cast<Character*>(mEntity);
	if (character) {
		Enemy* enemy = character->GetEnemy();
		if (enemy) {
			result = eSuccess;
		}
	}

	return result;
}