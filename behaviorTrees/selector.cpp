#include <stdafx.h>
#include "selector.h"

Selector::Selector(GameEntity* entity) :
	Group(entity) {}

Behavior::Status Selector::update() {
	while(true) {
		Status s = mChildren[mCurrentChild]->tick();
		if (eFail != s) {
			return s;
		}

		++mCurrentChild;

		if (mCurrentChild == mChildren.size()) {
			return eFail;
		}
	}

	return eInvalid;
}

void Selector::onEnter() {
	mCurrentChild = 0;
}