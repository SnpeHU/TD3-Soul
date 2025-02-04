#pragma once
#include "Tool/timer.h"
#include "Tool/MyVector2.h"
#include "Tool/MyVector3.h"
#include "StateNode.h"
#include "Novice.h"

class Beam;
class BlockEmitter;
class Charactor;
class Snake;




class BasicState : public StateNode
{
public:
	BasicState();
	~BasicState() = default;
	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:
	Timer timer;
	float totaltime = 1.0f;
	float passTime = 0.0f;

	int stateIndex;

	Snake* snake = nullptr;
	
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
	Vector3 targetDir;
	float moveDistance = 450.0f;

	Timer moveTimer;
	float moveTime = 8.0f;

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
	float upTime = 0.8f;
	float upHeight = 200.0f;

	Vector3 circleCenter;//圆心
	Timer toCircleLineTimer;//到达圆形线
	float toCircleLineTime = 0.2f;
	float radius = 30.0f;//头部旋转半径

	
	bool isUpOver = false;
	bool isFollowPlayer = false;

	Snake* snake = nullptr;

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
	float pushSpeed = 12.0f;
	bool isChangeGravity = false;

	int attackAudio = Novice::LoadAudio("./rs/attack.wav");

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
	float attackTime = 3.0f;

	Beam* beam = nullptr;
	float startDis = 60.0f;

	float beamForce = 4.0f;

	Snake* snake = nullptr;

	int beamAudio = Novice::LoadAudio("./rs/beam.wav");
};

class Chase : public StateNode
{
public:
	Chase();
	~Chase() = default;
	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:
	Timer chaseTimer;
	float chaseTime = 5.0f;

	bool isAttack = false;
	Charactor* target = nullptr;

	float attakeRange = 100.0f;
};

class Attack : public StateNode
{
public:
	Attack();
	~Attack() = default;
	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:
	Timer UpTimer;//頭を上げる
	float upTime = 0.8f;
	float upHeight = 100.0f;//頭を上げる高さ
	Vector3 upPos;//抬头位置
	Vector3 startPos;

	float pushSpeed = 10.0f;

	Timer attackTimer;
	float attackTime = 0.8f;
	Vector3 attackDir;

	bool isAttack = false;

	bool isSound = false;
};


class ToSecond : public StateNode
{
public:
	ToSecond();
	~ToSecond() = default;
	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:
	Timer timer;
	float totaltime = 2.0f;
	float passTime = 0.0f;
	
	bool isSound = false;
};

class RangeAttack : public StateNode
{
public:
	RangeAttack();
	~RangeAttack() = default;
	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:

	Vector2 firstPos;

	Vector2 perSize = { 200.0f,200.0f };
};