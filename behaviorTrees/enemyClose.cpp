#include <stdafx.h>
#include "enemyClose.h"
#include "gameEntity.h"
#include "character.h"
#include "enemy.h"

EnemyClose::EnemyClose(GameEntity* entity, float minDistance) :
	Behavior     (entity),
	mMinDistance (minDistance) {}

EnemyClose::Status EnemyClose::update() {
	Status result = eFail;

	Character* character = static_cast<Character*>(mEntity);
	if (character) {
		Enemy* enemy = character->GetEnemy();
		if (enemy) {
			float dist = (enemy->GetLoc() - character->GetLoc()).Length();
			if (enemy->IsDead() && !enemy->GetHit() && dist <= mMinDistance)
				result = eSuccess;
		}
	}

	return result;
}