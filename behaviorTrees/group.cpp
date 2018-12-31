#include <stdafx.h>
#include <tinyxml.h>
#include "group.h"

Group::Group(GameEntity* entity, const char* filename) :
	Behavior  (entity), 
	mFilename (filename) {}

Group::~Group() {

}

void Group::load() {
	if (mFilename) {
		TiXmlDocument doc(mFilename);
		if (!doc.LoadFile()) {
			fprintf(stderr, "Couldn't read state machine config from %s", mFilename);
			return;
		}

		TiXmlHandle hDoc(&doc);

		TiXmlElement* pBehaviorTree;
		pBehaviorTree = hDoc.FirstChildElement().Element();
		if (!pBehaviorTree) {
			fprintf(stderr, "Invalid format for %s", mFilename);
			return;
		}


		int defaultStateIndex = 0;
		pBehaviorTree->Attribute("default_state_index",&defaultStateIndex);
		TiXmlHandle hBehaviorTree(pBehaviorTree);
		TiXmlHandle hStates = hBehaviorTree.FirstChildElement("states");

		// States
		TiXmlElement* stateElem = hStates.FirstChild().Element();
		int stateIndex = 0;
		for (stateElem; stateElem; stateElem = stateElem->NextSiblingElement()) {
			int stateId = 0;
			stateElem->Attribute("id", &stateId);
			State* state = getStateInstance(stateId);
			if (state) {
				if (stateIndex == defaultStateIndex) {
					mCurrentState = state;
				}

				// Actions
				state->setEnterAction(getActionInstance(stateElem->FirstChildElement("enter_action")));
				state->setExitAction(getActionInstance(stateElem->FirstChildElement("exit_action")));
				state->setStateAction(getActionInstance(stateElem->FirstChildElement("state_action")));

				// Transitions
				TiXmlHandle hTransitions = stateElem->FirstChildElement("transitions");
				TiXmlElement* transitionElem = hTransitions.FirstChild().Element();
				for (transitionElem; transitionElem; transitionElem = transitionElem->NextSiblingElement()) {
					Condition* condition = nullptr;
					int conditionId = 0;
					TiXmlElement* conditionElem = transitionElem->FirstChildElement("condition");
					conditionElem->Attribute("id", &conditionId);
					switch (conditionId) {
					case 1: {
						condition = new CanSeeEnemy(*this);
						float distance = 0;
						conditionElem->Attribute("distance", &distance);
						static_cast<CanSeeEnemy*>(condition)->distance = distance;
						break;
					}
					case 2: {
						condition = new CanAttackEnemy(*this);
						float distance = 0;
						conditionElem->Attribute("distance", &distance);
						static_cast<CanAttackEnemy*>(condition)->distance = distance;
						break;
					}
					case 3: {
						condition = new CannotAttackEnemy(*this);
						float distance = 0;
						conditionElem->Attribute("distance", &distance);
						static_cast<CannotAttackEnemy*>(condition)->distance = distance;
						break;
					}
					case 4: {
						condition = new IsDead(*this);
						break;
					}
					case 5: {
						condition = new IsHit(*this);
						break;
					}
					case 6: {
						condition = new ReachedTargetPoint(*this);
						float distance = 0;
						conditionElem->Attribute("distance", &distance);
						static_cast<ReachedTargetPoint*>(condition)->distance = distance;
						break;
					}
					}

					TiXmlElement* targetStateElem = transitionElem->FirstChildElement("target_state");
					int targetStateId = 0;
					targetStateElem->Attribute("id", &targetStateId);
					State* targetState = getStateInstance(targetStateId);

					Action* triggerAction = getActionInstance(transitionElem->FirstChildElement("trigger_action"));

					state->addTransition(new Transition(condition, targetState, triggerAction));
				}
			}

			++stateIndex;
		}
	}
}