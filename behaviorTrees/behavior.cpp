#include <stdafx.h>
#include <tinyxml.h>
#include "behavior.h"
#include "gameEntity.h"
#include "sequence.h"
#include "selector.h"
#include "idle.h"
#include "enemyClose.h"
#include "attack.h"
#include "pursue.h"
#include "goTo.h"
#include "entityDead.h"
#include "isHit.h"
#include "restoreHit.h"
#include "globals.h"

Behavior::Behavior(GameEntity* entity) :
	mEntity (entity),
	mStatus(eInvalid) {}

Behavior::~Behavior() {
}

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

Behavior* Behavior::load(GameEntity* entity, const char* filename) {
	Behavior* behavior = nullptr;
	
	if (filename) {
		TiXmlDocument doc(filename);
		if (!doc.LoadFile()) {
			fprintf(stderr, "Couldn't read behavior tree config from %s", filename);
		}
		else {
			TiXmlHandle hDoc(&doc);

			TiXmlElement* pBehaviorTree;
			pBehaviorTree = hDoc.FirstChildElement(ROOT_NODE_NAME).ToElement();
			if (!pBehaviorTree) {
				fprintf(stderr, "Invalid format for %s", filename);
			}
			else {
				// Root node is not a Group and it only has one child (the first child), therefore any other siblings at this level are ignored, if present.
				TiXmlHandle hBehaviorTree(pBehaviorTree);
				TiXmlElement* behaviorElem = hBehaviorTree.FirstChild().ToElement();

				if (behaviorElem) {
					std::string nodeName = behaviorElem->ValueStr();
					if (!nodeName.compare(BEHAVIOR_NODE_NAME)) {
						behavior = getBehaviorInstance(entity, behaviorElem);
					}
					else if (!nodeName.compare(SELECTOR_NODE_NAME)) {
						Selector* selector = new Selector(entity);
						selector->load(behaviorElem);
						behavior = selector;
					}
					else if (!nodeName.compare(SEQUENCE_NODE_NAME)) {
						Sequence* sequence = new Sequence(entity);
						sequence->load(behaviorElem);
						behavior = sequence;
					}
				}
			}
		}
	}

	return behavior;
}

Behavior* Behavior::getBehaviorInstance(GameEntity* entity, TiXmlElement* behaviorElem) {
	Behavior* behavior = nullptr;
	int behaviorId = 0;
	behaviorElem->Attribute(ID_ATTR, &behaviorId);

	switch (behaviorId) {
		case B_Idle: {
			behavior = new Idle(entity);
			break;
		}
		case B_EnemyClose: {
			float minDistance = 0.f;
			behaviorElem->Attribute(MIN_DISTANCE_ATTR, &minDistance);
			if (!&minDistance) minDistance = 0.f;

			behavior = new EnemyClose(entity, minDistance);
			break;
		}
		case B_Attack: {
			int damage = 0;
			behaviorElem->Attribute(DAMAGE_POINTS_ATTR, &damage);
			if (!&damage) damage = 0;

			behavior = new Attack(entity, damage);
			break;
		}
		case B_Pursue: {
			behavior = new Pursue(entity);
			break;
		}
		case B_GoTo: {
			behavior = new GoTo(entity);
			break;
		}
		case B_EntityDead: {
			behavior = new EntityDead(entity);
			break;
		}
		case B_IsHit: {
			behavior = new IsHit(entity);
			break;
		}
		case B_RestoreHit: {
			behavior = new RestoreHit(entity);
			break;
		}
	}

	return behavior;
}