#include <stdafx.h>
#include "goTo.h"
#include "gameEntity.h"
#include "enemy.h"
#include "steering/arriveSteering.h"
#include "globals.h"

GoTo::GoTo(GameEntity* entity, USVec3D destination) :
	Behavior     (entity),
	mDestination (destination) {}

GoTo::Status GoTo::update() {
	/*
	GetOwner()->UpdatePath(m_Path);
if(CheckArrived())
returneSuccess;
elseif(CannotMove())
returneFail;
else
returneRunning;
	*/
	return eSuccess;
}

void GoTo::onEnter() {
	Enemy* enemy = static_cast<Enemy*>(mEntity);
	if (enemy) {
		USVec2D currentLoc = enemy->GetLoc();
		enemy->SetTargetPoint(mDestination.mX, mDestination.mY);
		enemy->SetSteering(new ArriveSteering(*enemy, enemy->GetTargetPoint()));
	}
	/*
	m_Path=Pathfinding::FindPath(
GetOwner()->Position(),
Destination()
);
	*/
}

void GoTo::onExit() {
	/*
	GetOwner()->PlayAnimation("Stop");
m_Path.Release();
	*/
}