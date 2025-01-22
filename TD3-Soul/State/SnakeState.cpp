#include "SnakeState.h"
#include "Object/Snake.h"
#include "Manager/CharactorManager.h"
#define deltaTime (1.0f/60.0f)

#pragma region BasicState
BasicState::BasicState()
{
	name = "Basic";
	timer.set_one_shot(true);
	timer.set_on_timeout([&]()
		{
			CharactorManager::Instance()->GetSnake()->SwitchState("Jump");
		});
	timer.set_wait_time(totaltime);
}
void BasicState::onEnter()
{
	timer.set_wait_time(totaltime);
	timer.restart();
}
void BasicState::onUpdate()
{
	timer.on_update(deltaTime);
}
#pragma endregion

#pragma region JumpState
JumpState::JumpState()
{
	name = "Jump";
	timer.set_one_shot(true);
	timer.set_on_timeout([&]()
		{
			
			CharactorManager::Instance()->GetSnake()->SwitchState("Basic");
		});
}

void JumpState::onEnter()
{
	timer.restart();
	timer.set_wait_time(totaltime);
	targetPos = CharactorManager::Instance()->GetPlayer()->GetPos();
	targetPos.z = 0.0f;
	startPos = CharactorManager::Instance()->GetSnake()->GetPos();
}

void JumpState::onUpdate()
{

	
	float t = timer.get_progress();
	if (t > 1.0f)
	{
		t = 1.0f;
	}
		Vector3 pos;
		pos.x = (1 - t) * startPos.x + t * targetPos.x;
		pos.y = (1 - t) * startPos.y + t * targetPos.y;
		pos.z = (1 - t) * startPos.z + t * targetPos.z + jumpHeight *(1 - t) * t * 4;
		CharactorManager::Instance()->GetSnake()->SetPos(pos);
	
	//else
	//{
	//	CharactorManager::Instance()->GetSnake()->SetPos(targetPos);
	//}
	timer.on_update(deltaTime);
}

void JumpState::onExit()
{
	/*CharactorManager::Instance()->GetSnake()->SetPos(targetPos);*/
}

#pragma endregion

#pragma region MoveState
MoveState::MoveState()
{
}

void MoveState::onEnter()
{
}

void MoveState::onUpdate()
{
}

void MoveState::onExit()
{
}
#pragma endregion
