#include "SnakeState.h"
#include "Object/Snake.h"
#include "Manager/CharactorManager.h"


#pragma region BasicState
BasicState::BasicState()
{
	name = "Basic";
	timer.set_one_shot(true);
	timer.set_on_timeout([&]()
		{
			//CharactorManager::Instance()->GetSnake()->SwitchState("Jump");
			CharactorManager::Instance()->GetSnake()->SwitchState("UpHead");
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

#pragma region CircleMove
CircleMove::CircleMove()
{
}

void CircleMove::onEnter()
{
}

void CircleMove::onUpdate()
{
}

void CircleMove::onExit()
{
}
#pragma endregion

#pragma region UpHead
UpHead::UpHead()
{
	name = "UpHead";
	upTimer.set_one_shot(true);
	upTimer.set_wait_time(upTime);
	upTimer.set_on_timeout([&]()
		{
			isUpOver = true;
			startPos = CharactorManager::Instance()->GetSnake()->GetPos();
			Vector3 dir = (CharactorManager::Instance()->GetPlayer()->GetPos() - startPos).normalize();
			targetPos.x = circleCenter.x + dir.x * radius;
			targetPos.y = circleCenter.y + dir.y * radius;

		});

	toCircleLineTimer.set_one_shot(true);
	toCircleLineTimer.set_wait_time(toCircleLineTime);
	toCircleLineTimer.set_on_timeout([&]()
		{
			isFollowPlayer = true;
			CharactorManager::Instance()->GetSnake()->SetAngleConstraint(2* M_PI,2* M_PI);
		});
}

void UpHead::onEnter()
{
	upTimer.restart();
	toCircleLineTimer.restart();
	startPos = CharactorManager::Instance()->GetSnake()->GetPos();
	targetPos = startPos;
	targetPos.z += upHeight;
	circleCenter = targetPos;
}

void UpHead::onUpdate()
{
	if (!isUpOver)
	{
		//上升
		float t = upTimer.get_progress();
		if (t > 1.0f)
		{
			t = 1.0f;
		}
		Vector3 pos;
		pos.x = (1 - t) * startPos.x + t * targetPos.x;
		pos.y = (1 - t) * startPos.y + t * targetPos.y;
		pos.z = (1 - t) * startPos.z + t * targetPos.z;
		CharactorManager::Instance()->GetSnake()->SetPos(pos);
		upTimer.on_update(deltaTime);

	}
	else if (!isFollowPlayer)
	{
		//到达圆形线
		float t = toCircleLineTimer.get_progress();
		if (t > 1.0f)
		{
			t = 1.0f;
		}
		Vector3 pos;
		pos.x = (1 - t) * startPos.x + t * targetPos.x;
		pos.y = (1 - t) * startPos.y + t * targetPos.y;
		pos.z = (1 - t) * startPos.z + t * targetPos.z;
		CharactorManager::Instance()->GetSnake()->SetPos(pos);
		toCircleLineTimer.on_update(deltaTime);
	}
	else
	{
		Vector3 dir = (CharactorManager::Instance()->GetPlayer()->GetPos() - startPos).normalize();
		CharactorManager::Instance()->GetSnake()->SetPos(Vector3(circleCenter.x + dir.x * radius, circleCenter.y + dir.y * radius, upHeight));
	}

}

void UpHead::onExit()
{
	isUpOver = false;
	isFollowPlayer = false;
}
#pragma endregion