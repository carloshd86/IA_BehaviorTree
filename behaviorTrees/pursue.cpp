#include <stdafx.h>
#include "pursue.h"
#include "gameEntity.h"
#include "character.h"
#include "enemy.h"

Pursue::Pursue(GameEntity* entity) :
	Behavior(entity) {}

Pursue::Status Pursue::update() {
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