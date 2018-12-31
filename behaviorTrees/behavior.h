#ifndef __BEHAVIOR_H__
#define __BEHAVIOR_H__

class GameEntity;

class Behavior {

public:
	enum Status {
		eInvalid,
		eSuccess,
		eFail,
		eRunning
	};

protected:
	Status update();
	void   onEnter();
	void   onExit();

public:
	Behavior(GameEntity* entity);

	GameEntity* getEntity() const;
	Status      tick();

private:
	Status      mStatus;
	GameEntity* mEntity;
};

#endif