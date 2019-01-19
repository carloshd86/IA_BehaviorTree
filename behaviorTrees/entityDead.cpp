#include <stdafx.h>
#include "entityDead.h"
#include "gameEntity.h"
#include "character.h"
#include "enemy.h"

EntityDead::EntityDead(GameEntity* entity) :
	Behavior     (entity) {}

EntityDead::Status EntityDead::update() {
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