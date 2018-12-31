#ifndef __BEHAVIOR_H__
#define __BEHAVIOR_H__

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
	Behavior();

	Status tick();

private:
	Status mStatus;
};

#endif