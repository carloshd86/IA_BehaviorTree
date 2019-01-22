#include <stdafx.h>
#include "goTo.h"
#include "gameEntity.h"
#include "steering/arriveSteering.h"
#include "globals.h"

const float GoTo::MIN_DISTANCE_NEXT_POINT = 100;

GoTo::GoTo(GameEntity* entity) :
	Behavior(entity),
	mDestination(0.f, 0.f, 0.f),
	mRandomDestination(true),
	mInitialized(false) {}

GoTo::GoTo(GameEntity* entity, USVec3D destination) :
	Behavior           (entity),
	mDestination       (destination),
	mRandomDestination (false) {}

void GoTo::onEnter() {
	if (mEntity) {
		mEntity->SetImage(I_Windup);
		// m_Path=Pathfinding::FindPath(GetOwner()->Position(), Destination());
		if (mRandomDestination) {
			GenerateRandomDestination();
		}

		USVec2D currentLoc = mEntity->GetLoc();
		mEntity->SetTargetPoint(mDestination.mX, mDestination.mY);
		mEntity->SetSteering(new ArriveSteering(*mEntity, mEntity->GetTargetPoint()));
	}
	mInitialized = true;
}

GoTo::Status GoTo::update() {
	if (!mInitialized) onEnter();
	Status result = eFail;
	if (mEntity) {
		// GetOwner()->UpdatePath(m_Path);
		result = eRunning;
		if (mEntity->CheckArrivedTargetPoint()) {
			result = eSuccess;
		}
		/*else if (mEntity->CannotMove()) {
			result = eFail;
		}*/
	}

	return result;
}

void GoTo::onExit() {
	//mStatus = eInvalid;
	mInitialized = false;
	if (mEntity) {
		mEntity->SetImage(I_Default);
		mEntity->SetSteering(nullptr);
		mEntity->SetLinearVelocity(0.f, 0.f);
	}
	/*
	GetOwner()->PlayAnimation("Stop");
	m_Path.Release();
	*/
}

void GoTo::GenerateRandomDestination() {
	USVec2D currentLoc = mEntity->GetLoc();
	int attempts = 100;
	do {
		--attempts;
		mDestination = USVec2D(Rand(-MAX_VIEWPORT_WIDTH_HALF, MAX_VIEWPORT_WIDTH_HALF), Rand(-MAX_VIEWPORT_HEIGHT_HALF, MAX_VIEWPORT_HEIGHT_HALF));
	} while (attempts && currentLoc.DistSqrd(mDestination) < MIN_DISTANCE_NEXT_POINT * MIN_DISTANCE_NEXT_POINT);
}