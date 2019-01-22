#ifndef __BEHAVIOR_H__
#define __BEHAVIOR_H__

class GameEntity;
class TiXmlElement;

class Behavior {

public:
	enum Status {
		eInvalid,
		eSuccess,
		eFail,
		eRunning
	};

protected:
	virtual Status update();
	virtual void   onEnter();
	virtual void   onExit();

public:
	Behavior(GameEntity* entity);
	virtual ~Behavior();

	GameEntity* getEntity() const;
	Status      tick();

	static Behavior* load(GameEntity* entity, const char* mFilename);

protected:
	Status      mStatus;
	GameEntity* mEntity;
	
	static Behavior* getBehaviorInstance(GameEntity* entity, TiXmlElement* behaviorElem);
};

#endif