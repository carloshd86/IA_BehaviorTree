#include <stdafx.h>
#include "enemy.h"
#include <tinyxml.h>

#include <params.h>
#include <steering\pursueSteering.h>
#include <steering/alignToMovementSteering.h>
#include <character.h>
#include <behaviorTrees/behavior.h>

const float Enemy::MIN_DISTANCE_TO_REACH_TARGET = 25.f;

Enemy::Enemy() : 
	mLinearVelocity  (0.0f, 0.0f), 
	mAngularVelocity (0.0f),
	mSteering        (nullptr),
	mAlignSteering   (nullptr),
	mTarget          (nullptr),
	mBehavior        (nullptr),
	mLifePoints      (1),
	mHit             (false)

{
	RTTI_BEGIN
		RTTI_EXTEND (MOAIEntity2D)
	RTTI_END
}

Enemy::~Enemy()
{
	if (mSteering) delete mSteering;	
	if (mAlignSteering) delete mAlignSteering;
}

void Enemy::SetTarget(GameEntity& target)
{
	mTarget = &target;
}

void Enemy::OnStart()
{
    ReadParams("params.xml", mParams);
	mLinearVelocity.NormSafe();
	mLinearVelocity	*= mParams.enemy_speed;
	//if (mTarget)
	//	mSteering = new PursueSteering(*this, *mTarget);

	mAlignSteering = new AlignToMovementSteering(*this);

	mBehavior = Behavior::load(this, "enemy_bt.xml");
}

void Enemy::OnStop()
{

}

void Enemy::OnUpdate(float step)
{
	//mBehavior->update();

	USVec3D pos             = GetLoc();
	float   rot             = GetRot();

	pos.mX += mLinearVelocity.mX * step;
	pos.mY += mLinearVelocity.mY * step;

	rot += mAngularVelocity * step;

	SetLoc(pos);
	SetRot(rot);

	if (mSteering) {
		USVec2D linearAcceleration = mSteering->GetSteering();
		mLinearVelocity.mX += linearAcceleration.mX * step;
		mLinearVelocity.mY += linearAcceleration.mY * step;
	}

	if (mAlignSteering) {
		float angularAcceleration = mAlignSteering->GetSteering();
		mAngularVelocity += angularAcceleration * step;
	}

	SetLoc(pos);
}

void Enemy::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	if (mSteering)      mSteering->DrawDebug();
	if (mAlignSteering) mAlignSteering->DrawDebug();
}

void Enemy::SetLifePoints(int lifePoints) {
	if (lifePoints < 0) lifePoints = 0;
	mLifePoints = lifePoints;
}

void Enemy::Damage(int lifePoints) {
	SetLifePoints(mLifePoints - lifePoints);
	mHit = true;
}

bool Enemy::IsDead() {
	return mLifePoints <= 0;
}

bool Enemy::GetHit() {
	return mHit;
}

void Enemy::SetHit(bool hit) {
	mHit = hit;
}

USVec2D Enemy::GetTargetPoint() {
	return mTargetPoint;
}

void Enemy::SetTargetPoint(float x, float y) {
	mTargetPoint.mX = x;
	mTargetPoint.mY = y;
}

void Enemy::SetSteering(ISteering* steering) {
	if (mSteering) delete mSteering;
	mSteering = steering;
}


// Lua configuration

void Enemy::RegisterLuaFuncs(MOAILuaState& state)
{
	MOAIEntity2D::RegisterLuaFuncs(state);
	
	luaL_Reg regTable [] = {
		{ "setLinearVel",			_setLinearVel},
		{ "setAngularVel",			_setAngularVel},
		{ "setTarget",			    _setTarget},
	    { "setLifePoints",			_setLifePoints},
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

int Enemy::_setLinearVel(lua_State* L)
{
	MOAI_LUA_SETUP(Enemy, "U")
	
	float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(3, 0.0f);
	self->SetLinearVelocity(pX, pY);
	return 0;	
}

int Enemy::_setAngularVel(lua_State* L)
{
	MOAI_LUA_SETUP(Enemy, "U")
	
	float angle = state.GetValue<float>(2, 0.0f);
	self->SetAngularVelocity(angle);

	return 0;
}
	
int Enemy::_setTarget(lua_State* L)
{
	MOAI_LUA_SETUP(Enemy, "U")

	GameEntity * entity = state.GetLuaObject<Character>(2, true);
	if (entity)
		self->SetTarget(*entity);
	return 0;	
}

int Enemy::_setLifePoints(lua_State* L)
{
	MOAI_LUA_SETUP(Enemy, "U")

	int lifePoints = state.GetValue<int>(2, true);
	self->SetLifePoints(lifePoints);

	return 0;	
}