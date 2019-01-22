#include <stdafx.h>
#include "pursue.h"
#include "gameEntity.h"
#include "character.h"
#include "enemy.h"
#include "steering/pursueSteering.h"
#include "globals.h"

Pursue::Pursue(GameEntity* entity) :
	Behavior(entity),
	mInitialized(false) {}

void Pursue::onEnter() {
	if (mEntity) {
		mEntity->SetImage(I_Alarm);
		Character* character = static_cast<Character*>(mEntity);
		if (character) {
			Enemy* enemy = character->GetEnemy();
			if (enemy) {
				character->SetSteering(new PursueSteering(*character, *enemy));
			}
		}
	}
	mInitialized = true;
}

Pursue::Status Pursue::update() {
	if (!mInitialized) onEnter();
	Status result = eFail;
	if (mEntity) {
		result = eRunning;
		Character* character = static_cast<Character*>(mEntity);
		if (character) {
			Enemy* enemy = character->GetEnemy();
			if (enemy) {
				float distSqr = (USVec2D(enemy->GetLoc()) - USVec2D(character->GetLoc())).LengthSquared();
				if (distSqr <= 2500.f) result = eSuccess;
			}
		}
	}
	return result;
}

void Pursue::onExit() {
	//mStatus = eInvalid;
	mInitialized = false;
	if (mEntity) {
		mEntity->SetImage(I_Default);
		mEntity->SetSteering(nullptr);
		mEntity->SetLinearVelocity(0.f, 0.f);
	}
}