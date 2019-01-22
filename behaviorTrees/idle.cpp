#include <stdafx.h>
#include "idle.h"
#include "gameEntity.h"

Idle::Idle(GameEntity* entity) :
	Behavior(entity) {}

void Idle::onEnter() {
	return Behavior::onExit();
}

Idle::Status Idle::update() {
	return Behavior::update();
}

void Idle::onExit() {
	Behavior::onExit();
}