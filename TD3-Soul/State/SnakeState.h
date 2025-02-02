#pragma once
#include "Tool/timer.h"
#include "Tool/MyVector2.h"
#include "Tool/MyVector3.h"
#include "StateNode.h"

class Beam;
class BlockEmitter;

class BasicState : public StateNode
{
public:
	BasicState();
	~BasicState() = default;
	void onEnter() override;
	void onUpdate() override;
	//virtual void onExit() override;
private:
	Timer timer;
	float totaltime = 3.0f;
	float passTime = 0.0f;

	
};

class JumpState : public StateNode
{
public:
	JumpState();
	~JumpState() = default;
	void onEnter() override;
	void onUpdate() override;
	void onExit() override;


private:
	Timer timer;
	Vector3 targetPos;
	Vector3 startPos;
	float totaltime = 1.0f;
	float passTime = 0.0f;

	float jumpHeight = 300.0f;

};

class MoveState : public StateNode
{
public:
	MoveState();
	~MoveState() = default;
	void onEnter() override;
	void onUpdate() override;
	void onExit() override;

private:
	Vector3 targetPos;
	float moveDistance = 400.0f;

};

class CircleMove : public StateNode
{
public:
	CircleMove();
	~CircleMove() = default;
	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
};

class UpHead : public StateNode
{
public:
	UpHead();
	~UpHead() = default;
	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:
	Vector3 startPos;
	Vector3 targetPos;

	Timer upTimer;//上げる
	float upTime = 0.5f;
	float upHeight = 200.0f;

	Vector3 circleCenter;//圆心
	Timer toCircleLineTimer;//到达圆形线
	float toCircleLineTime = 0.2f;
	float radius = 40.0f;//头部旋转半径

	
	bool isUpOver = false;
	bool isFollowPlayer = false;

};

//抬头结束后，冲向玩家
class PushHead : public StateNode
{
public:
	PushHead();
	~PushHead() = default;
	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:
	float pushSpeed = 10.0f;
	bool isChangeGravity = false;

};


class BeamAttack : public StateNode
{
public:
	BeamAttack();
	~BeamAttack() = default;
	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:
	Timer attackTimer;
	float attackTime = 10.0f;

	Beam* beam = nullptr;

};