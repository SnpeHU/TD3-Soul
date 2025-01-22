#pragma once
#include "Tool/timer.h"
#include "Tool/MyVector2.h"
#include "Tool/MyVector3.h"
#include "StateNode.h"



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
	float totaltime = 1.0f;
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