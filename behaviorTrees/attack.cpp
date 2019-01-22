#include <stdafx.h>
#include "attack.h"
#include "gameEntity.h"
#include "character.h"
#include "enemy.h"
#include "globals.h"

Attack::Attack(GameEntity* entity, int damage) :
	Behavior (entity),
	mDamage  (damage) {}

void Attack::onEnter() {
}

Attack::Status Attack::update() {
	if (mEntity) {
		mEntity->SetImage(I_Attack);
		Character* character = static_cast<Character*>(mEntity);
		if (character) {
			Enemy* enemy = character->GetEnemy();
			if (enemy) {
				enemy->Damage(mDamage);
			}
		}
	}
	return eSuccess;
}

void Attack::onExit() {
	//mStatus = eInvalid;
	if (mEntity) {
		mEntity->SetImage(I_Default);
	}
}