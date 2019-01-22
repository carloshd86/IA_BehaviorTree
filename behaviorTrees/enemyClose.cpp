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

	if (mMinDistance > 0) {
		Character* character = static_cast<Character*>(mEntity);
		if (character) {
			Enemy* enemy = character->GetEnemy();
			if (enemy) {
				float distSqr = (USVec2D(enemy->GetLoc()) - USVec2D(character->GetLoc())).LengthSquared();
				if (!enemy->IsDead() && !enemy->GetHit() && distSqr <= mMinDistance * mMinDistance)
					result = eSuccess;
			}
		}
	}

	return result;
}