#pragma once
#include "Tool/timer.h"
#include "Tool/MyVector2.h"
#include "Tool/MyVector3.h"
#include "StateNode.h"
class Object;
class PlayerBullet;
class FollowState : public StateNode
{
public:
	FollowState(PlayerBullet* owner);
	~FollowState() = default;
	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:


	PlayerBullet* owner = nullptr;

};


class AimState : public StateNode
{
public:
	AimState(PlayerBullet* owner);
	~AimState() = default;
	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:
	PlayerBullet* owner = nullptr;

	Timer aimTimer;
	float minTime = 0.2f;
	float increTime = 0.2f;
	float currentTime = minTime;//当前等级需要的时间

	int powerLevel = 0;
	int maxPowerLevel = 3;

	float basicspeed = 5.0f;
};

class ShootedState : public StateNode
{
public:
	ShootedState(PlayerBullet* owner);
	~ShootedState() = default;
	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:
	PlayerBullet* owner = nullptr;

	Timer pickTimer;//发射后多久可以回收
	float pickTime = 0.5f;
};