#include <stdafx.h>
#include "behavior.h"

Behavior::Behavior() {}

Behavior::Status Behavior::tick() {
	if (eInvalid == mStatus) {
		onEnter();
	}

	mStatus=update();

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