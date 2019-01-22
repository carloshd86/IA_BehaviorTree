#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <gameEntity.h>
#include "steering/iAlignSteering.h"
#include "pathPoints.h"
#include "obstacles.h"

class Behavior;

class Enemy: public GameEntity
{
public:
    DECL_LUA_FACTORY(Enemy)
protected:
	virtual void OnStart();
	virtual void OnStop();
	virtual void OnUpdate(float step);
public:
	virtual void DrawDebug();

	Enemy();
	~Enemy();
	
	void SetTarget(GameEntity& target);
	void SetLinearVelocity(float x, float y) { mLinearVelocity.mX = x; mLinearVelocity.mY = y;}
	void SetAngularVelocity(float angle) { mAngularVelocity = angle;}
	
	USVec2D GetLinearVelocity() const { return mLinearVelocity;}
	float GetAngularVelocity() const { return mAngularVelocity;}

	const Params& GetParams() const { return mParams; }
	const PathPoints& GetPathPoints() const { return mPathPoints; }
	const Obstacles& GetObstacles() const { return mObstacles; }

	void    SetLifePoints  (int lifePoints);
	void    Damage         (int lifePoints);
	bool    IsDead         () const;
	bool    GetHit         () const;
	void    SetHit         (bool hit);
	USVec2D GetTargetPoint () const;
	void    SetTargetPoint (float x, float y);
	void    SetSteering    (ISteering* steering);
	void    RemoveSteering ();
	bool    CheckArrivedTargetPoint();
	bool    CannotMove();
	void    Kill();

private:

	static const float MIN_DISTANCE_TO_REACH_TARGET;

	USVec2D mLinearVelocity;
	float mAngularVelocity;
	
	Params mParams;
	PathPoints mPathPoints;
	Obstacles mObstacles;

	ISteering*      mSteering;
	IAlignSteering* mAlignSteering;
	GameEntity*     mTarget;
	Behavior*       mBehavior;

	int  mLifePoints;
	bool mHit;
	USVec2D mTargetPoint;

	// Lua configuration
public:
	virtual void RegisterLuaFuncs(MOAILuaState& state);
private:
	static int _setLinearVel(lua_State* L);
	static int _setAngularVel(lua_State* L);
	static int _setTarget(lua_State* L);
	static int _setLifePoints(lua_State* L);
};

#endif