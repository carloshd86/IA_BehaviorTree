#include <stdafx.h>
#include "sequence.h"

Sequence::Sequence(GameEntity* entity) :
	Group(entity) {}

Behavior::Status Sequence::update() {
	while(true) {
		Status s = mChildren[mCurrentChild]->tick();
		if (eSuccess != s) {
			return s;
		}

		++mCurrentChild;

		if (mCurrentChild == mChildren.size()) {
			return eSuccess;
		}
	}

	return eInvalid;
}

void Sequence::onEnter() {
	mCurrentChild = 0;
}