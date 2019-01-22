#include <stdafx.h>
#include "restoreHit.h"
#include "gameEntity.h"
#include "enemy.h"
#include "globals.h"

RestoreHit::RestoreHit(GameEntity* entity) :
	Behavior     (entity) {}

Behavior::Status RestoreHit::update() {
	Status result = eFail;

	Enemy* enemy = static_cast<Enemy*>(mEntity);
	if (enemy) {
		enemy->SetHit(false);
		result = eSuccess;
	}

	return result;
}

void RestoreHit::onExit() {
	//mStatus = eInvalid;
}