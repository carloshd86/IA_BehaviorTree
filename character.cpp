#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>

#include <params.h>
#include <steering/obstacleAvoidanceSteering.h>
#include <steering/pathFollowingSteering.h>
#include <steering/arriveSteering.h>
#include <steering/alignToMovementSteering.h>
#include <behaviorTrees/behavior.h>
#include <enemy.h>
#include "globals.h"

const float Character::MIN_DISTANCE_TO_REACH_TARGET = 25.f;

Character::Character() : 
	mLinearVelocity  (0.0f, 0.0f), 
	mAngularVelocity (0.0f),
	mAlignSteering   (nullptr),
	mBehavior        (nullptr),
	mEnemy           (nullptr)
{
	RTTI_BEGIN
		RTTI_EXTEND (MOAIEntity2D)
	RTTI_END
}

Character::~Character()
{

	ClearSteeringWeights();
	if (mAlignSteering) delete mAlignSteering;
	if (mBehavior)      delete mBehavior;
}

void Character::OnStart()
{
    ReadParams("params.xml", mParams);
	//ReadPathPoints("path.xml", mPathPoints);
	//ReadObstacles("obstacles.xml", mObstacles);
	//mSteeringWeights.push_back(SteeringWeight(new PathFollowingSteering(*this, mParams.targetPosition), 0.2f));
	//mSteeringWeights.push_back(SteeringWeight(new ObstacleAvoidanceSteering(*this), 0.8f));
	//mSteeringWeights.push_back(SteeringWeight(new ArriveSteering(*this, mParams.targetPosition), 1.f));

	mAlignSteering = new AlignToMovementSteering(*this);

	mBehavior = Behavior::load(this, "character_bt.xml");
}

void Character::OnStop()
{

}

void Character::OnUpdate(float step)
{
	if (mBehavior) mBehavior->tick();

	USVec3D pos             = GetLoc();
	float   rot             = GetRot();

	pos.mX += mLinearVelocity.mX * step;
	pos.mY += mLinearVelocity.mY * step;

	rot += mAngularVelocity * step;

	SetLoc(pos);
	SetRot(rot);
	
	size_t numSteerings = mSteeringWeights.size();
	USVec2D linearAcceleration { 0.f, 0.f };
	for (size_t i = 0; i < numSteerings; ++i) {
		USVec2D loopSteering = mSteeringWeights[i].steering->GetSteering();
		loopSteering.NormSafe();
		linearAcceleration += loopSteering * mSteeringWeights[i].weight;
	}

	AdjustAccelerationModule(linearAcceleration);

	mLinearVelocity.mX += linearAcceleration.mX * step;
	mLinearVelocity.mY += linearAcceleration.mY * step;

	if (mAlignSteering) {
		float angularAcceleration = mAlignSteering->GetSteering();
		mAngularVelocity += angularAcceleration * step;
	}
}

void Character::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

	gfxDevice.SetPenColor(0.75f, 0.75f, 1.0f, 0.5f);
	size_t pathParamsSize = mPathPoints.points.size();
	if (pathParamsSize > 1) {
		for (size_t i = 0; i < pathParamsSize - 1; ++i) {
			MOAIDraw::DrawLine(mPathPoints.points[i].mX, mPathPoints.points[i].mY, mPathPoints.points[i + 1].mX, mPathPoints.points[i + 1].mY);
		}
	}


	gfxDevice.SetPenColor(0.5f, 0.5f, 0.5f, 0.25f);
	size_t obstaclesSize = mObstacles.obstacles.size();
	if (obstaclesSize) {
		for (size_t i = 0; i < obstaclesSize; ++i) {
			MOAIDraw::DrawEllipseFill(mObstacles.obstacles[i].mX, mObstacles.obstacles[i].mY, mObstacles.obstacles[i].mZ, mObstacles.obstacles[i].mZ, 50);
		}
	}

	for (SteeringWeight& steeringWeight : mSteeringWeights) {
		if (steeringWeight.steering) steeringWeight.steering->DrawDebug();
	}
	if (mAlignSteering) mAlignSteering->DrawDebug();
}

void Character::ClearSteeringWeights() {
	for (SteeringWeight& steeringWeight : mSteeringWeights) delete steeringWeight.steering;
	mSteeringWeights.clear();
}

void Character::AddSteeringWeight(SteeringWeight& steeringWeight) {
	mSteeringWeights.push_back(steeringWeight);
}


void Character::AdjustAccelerationModule(USVec2D& acceleration)
{
	acceleration.NormSafe();
	acceleration *= mParams.max_acceleration;
}

void Character::SetEnemy(Enemy& enemy)
{
	mEnemy = &enemy;
}

Enemy* Character::GetEnemy() 
{
	return mEnemy;
}

bool Character::IsDead() const {
	return false;
}

USVec2D Character::GetTargetPoint() const {
	return mTargetPoint;
}

void Character::SetTargetPoint(float x, float y) {
	mTargetPoint.mX = x;
	mTargetPoint.mY = y;
}

void Character::SetSteering(ISteering* steering) {
	ClearSteeringWeights();
	if (steering) {
		AddSteeringWeight(Character::SteeringWeight(steering, 1.f));
	}
}

void Character::RemoveSteering() {
	SetSteering(nullptr);
}

bool Character::CheckArrivedTargetPoint() {
	return (USVec2D(GetLoc()).DistSqrd(mTargetPoint) <= MIN_DISTANCE_TO_REACH_TARGET * MIN_DISTANCE_TO_REACH_TARGET);
}

bool Character::CannotMove() {
	return GetLinearVelocity().LengthSquared() <= NEAR_ZERO_EPSILON;
}

void Character::Kill() {
	SetImage(I_Dead);
	RemoveSteering();
	SetLinearVelocity(0.f, 0.f);
	SetAngularVelocity(0.f);
}

// Lua configuration

void Character::RegisterLuaFuncs(MOAILuaState& state)
{
	MOAIEntity2D::RegisterLuaFuncs(state);
	
	luaL_Reg regTable [] = {
		{ "setLinearVel",			_setLinearVel},
		{ "setAngularVel",			_setAngularVel},
		{ "setEnemy",			    _setEnemy},
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

int Character::_setLinearVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(3, 0.0f);
	self->SetLinearVelocity(pX, pY);
	return 0;	
}

int Character::_setAngularVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float angle = state.GetValue<float>(2, 0.0f);
	self->SetAngularVelocity(angle);

	return 0;
}

int Character::_setEnemy(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")

	Enemy* entity = state.GetLuaObject<Enemy>(2, true);
	if (entity)
		self->SetEnemy(*entity);
	return 0;	
}