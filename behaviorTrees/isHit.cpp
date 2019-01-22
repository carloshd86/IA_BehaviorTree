#include <stdafx.h>
#include "isHit.h"
#include "gameEntity.h"
#include "enemy.h"
#include "globals.h"

IsHit::IsHit(GameEntity* entity) :
	Behavior     (entity) {}

IsHit::Status IsHit::update() {
	Status result = eFail;

	Enemy* enemy = static_cast<Enemy*>(mEntity);
	if (enemy && enemy->GetHit()) {
		result = eSuccess;
	}

	return result;
}