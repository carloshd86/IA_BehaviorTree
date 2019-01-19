#include <stdafx.h>
#include <tinyxml.h>
#include "group.h"
#include "sequence.h"
#include "selector.h"
#include "globals.h"

Group::Group(GameEntity* entity) :
	Behavior  (entity) {}

Group::~Group() {
	for (Behavior* behavior : mChildren) {
		delete behavior;
	}
}

void Group::load(TiXmlElement* groupElem) {
	if (groupElem) {
		// Loop through siblings to replicate the tree structure of the config file.
		TiXmlElement* behaviorElem = groupElem->FirstChildElement();
		for (behaviorElem; behaviorElem; behaviorElem = behaviorElem->NextSiblingElement()){
			std::string nodeName = behaviorElem->ValueStr();
			Behavior* behavior = nullptr;
			if (!nodeName.compare(BEHAVIOR_NODE_NAME)) {
				behavior = getBehaviorInstance(mEntity, behaviorElem);
			} else if (!nodeName.compare(SELECTOR_NODE_NAME)) {
				Selector* selector = new Selector(mEntity);
				selector->load(behaviorElem);
				behavior = selector;
			} else if (!nodeName.compare(SEQUENCE_NODE_NAME)) {
				Sequence* sequence = new Sequence(mEntity);
				sequence->load(behaviorElem);
				behavior = sequence;
			}
			if (behavior) mChildren.push_back(behavior);
		}
	}
}