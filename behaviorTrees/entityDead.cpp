#include <stdafx.h>
#include "entityDead.h"
#include "gameEntity.h"
#include "globals.h"

EntityDead::EntityDead(GameEntity* entity) :
	Behavior     (entity) {}

EntityDead::Status EntityDead::update() {
	Status result = eFail;

	if (mEntity && mEntity->IsDead()) {
		result = eSuccess;
	}

	return result;
}