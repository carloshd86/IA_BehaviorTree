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
#include "globals.h"

Behavior::Behavior(GameEntity* entity) :
	mEntity (entity) {}

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

	return behavior;
}

Behavior* Behavior::getBehaviorInstance(GameEntity* entity, TiXmlElement* behaviorElem) {
	Behavior* behavior = nullptr;
	int behaviorId = 0;
	behaviorElem->Attribute(ID_ATTR, &behaviorId);

	switch (behaviorId) {
		case B_Idle: {
			int radius = 0;
			behaviorElem->Attribute(RADIUS_ATTR, &radius);
			if (!&radius) radius = 0;

			int iReverse = 0;
			behaviorElem->Attribute(REVERSE_ATTR, &iReverse);
			bool reverse = false;
			if (!&iReverse) reverse = false;
			else reverse = iReverse;

			float speed = 0.f;
			behaviorElem->Attribute(SPEED_ATTR, &speed);
			if (!&speed) speed = 0.f;

			behavior = new Idle(entity, radius, reverse, speed);
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
			USVec3D destination;
			// TODO generate random destination
			// USVec3D destination = GoTo::GenerateRandomDestination();
			behavior = new GoTo(entity, destination);
			break;
		}
		case B_EntityDead: {
			behavior = new EntityDead(entity);
			break;
		}
	}

	return behavior;
}