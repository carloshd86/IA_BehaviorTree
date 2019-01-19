#include <stdafx.h>
#include "attack.h"
#include "gameEntity.h"
#include "character.h"
#include "enemy.h"

Attack::Attack(GameEntity* entity, int damage) :
	Behavior (entity),
	mDamage  (damage) {}

Attack::Status Attack::update() {
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