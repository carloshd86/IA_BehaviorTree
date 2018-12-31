#include <stdafx.h>
#include "behavior.h"
#include "gameEntity.h"

Behavior::Behavior(GameEntity* entity) :
	mEntity (entity) {}

Behavior::Status Behavior::tick() {
	if (eInvalid == mStatus) {
		onEnter();
	}

	mStatus = update();

	if (eRunning != mStatus) {
		onExit();
	}

	return mStatus;
}

Behavior::Status Behavior::update() {
	return eSuccess;
}

void Behavior::onEnter() {
}

void Behavior::onExit() {
}

GameEntity* Behavior::getEntity() const {
	return mEntity;
}