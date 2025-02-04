#include "SnakeState.h"
#include "Object/Snake.h"
#include "Manager/CharactorManager.h"
#include "Object/Beam.h"
#include "Camera.h"
extern Camera m_camera;


#pragma region BasicState
BasicState::BasicState()
{
	name = "Basic";
	snake = CharactorManager::Instance()->GetSnake();
	timer.set_one_shot(true);
	timer.set_on_timeout([&]()
		{
			//CharactorManager::Instance()->GetSnake()->SwitchState("Jump");
			stateIndex = rand() % 2;
			switch (stateIndex)
			{
			case 0:
				if (snake->phases == 0)
				{
					
					snake->SwitchState("UpHead");
				}
				else
				{
					snake->SwitchState("Jump");
				}
				break;
			case 1:
				CharactorManager::Instance()->GetSnake()->SwitchState("Chase");
				//CharactorManager::Instance()->GetSnake()->SwitchState("UpHead");
				break;
			default:
				break;
			}

			

			
		});
	timer.set_wait_time(totaltime);
}
void BasicState::onEnter()
{
	CharactorManager::Instance()->GetSnake()->SetEnableResistance(true);
	snake = CharactorManager::Instance()->GetSnake();
	timer.set_wait_time(totaltime);
	timer.restart();
}
void BasicState::onUpdate()
{
	timer.on_update(deltaTime);
}
void BasicState::onExit()
{
	snake = nullptr;
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
	//目标位置为地图中心与玩家位置的反方向延长线上的一个点
	Vector3 dir = CharactorManager::Instance()->GetPlayer()->GetPos().normalize() * -1;
	targetPos = { dir.x * moveDistance,dir.y * moveDistance,0.0f };
	CharactorManager::Instance()->GetSnake()->SwitchBehavior(Snake::SnakeBehavior::Smove);

	moveTimer.restart();
	moveTimer.set_one_shot(true);
	moveTimer.set_wait_time(moveTime);
	moveTimer.set_on_timeout([&]()
		{
		
			CharactorManager::Instance()->GetSnake()->SwitchState("Basic");
		});

}

void MoveState::onUpdate()
{
	targetDir = (targetPos - CharactorManager::Instance()->GetSnake()->GetPos()).normalize();
	CharactorManager::Instance()->GetSnake()->SetVelocity(targetDir * 6.0f);
	moveTimer.on_update(deltaTime);

	if ((targetPos - CharactorManager::Instance()->GetSnake()->GetPos()).length() < 100.0f)
	{
		CharactorManager::Instance()->GetSnake()->SwitchState("Basic");
	}
}

void MoveState::onExit()
{
	CharactorManager::Instance()->GetSnake()->SwitchBehavior(Snake::SnakeBehavior::Normol);
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
	snake = CharactorManager::Instance()->GetSnake();
	upTimer.set_one_shot(true);
	upTimer.set_wait_time(upTime);
	upTimer.set_on_timeout([&]()
		{
			isUpOver = true;
			startPos = snake->GetPos();
			Vector3 dir = (CharactorManager::Instance()->GetPlayer()->GetPos() - startPos).normalize();
			targetPos.x = circleCenter.x + dir.x * radius;
			targetPos.y = circleCenter.y + dir.y * radius;

		});

	toCircleLineTimer.set_one_shot(true);
	toCircleLineTimer.set_wait_time(toCircleLineTime);
	toCircleLineTimer.set_on_timeout([&]()
		{
			isFollowPlayer = true;
			snake->SetAngleConstraint(M_PI,M_PI);
			if (snake->GetPhases() == 0)
			{

				if (snake->aliveNodeNum <= 5)
				{
	

					Vector2 dir = { CharactorManager::Instance()->GetPlayer()->GetPos().x - snake->GetPos().x,CharactorManager::Instance()->GetPlayer()->GetPos().y - snake->GetPos().y };
					snake->SetVelocity(Vector3(dir.x, dir.y, 0.0f).normalize() * 2.0f);
					snake->SwitchState("ToSecond");

				}
				else
				{
					if (rand() % 100 < 40)
					{
						snake->SwitchState("PushHead");
					}
					else
					{
						snake->SwitchState("BeamAttack");
					}
				}
			}

			//有50%的概率冲向玩家

		});
}

void UpHead::onEnter()
{
	upTimer.restart();
	toCircleLineTimer.restart();
	snake = CharactorManager::Instance()->GetSnake();
	startPos = snake->GetPos();
	snake->SetNodeEnableGravity(false);
	snake->SetAngleConstraint(2* M_PI,2* M_PI);
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
		snake->SetPos(pos);
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
		snake->SetPos(pos);
		toCircleLineTimer.on_update(deltaTime);
	}

}

void UpHead::onExit()
{
	isUpOver = false;
	isFollowPlayer = false;
}
#pragma endregion

#pragma region PushHead
PushHead::PushHead()
{
	name = "PushHead";
}

void PushHead::onEnter()
{
	Snake* snake = CharactorManager::Instance()->GetSnake();
	Vector3 dir = (CharactorManager::Instance()->GetPlayer()->GetPos() - snake->GetPos()).normalize();
	snake->SetVelocity(dir * pushSpeed);
	snake->SetEnableResistance(true);


}

void PushHead::onUpdate()
{
	if (!isChangeGravity)
	{
		if(CharactorManager::Instance()->GetSnake()->GetIsOnGround())
		{
			CharactorManager::Instance()->GetSnake()->SetNodeEnableGravity(true);
			m_camera.Shake(8.0f, 0.4f);
			Novice::PlayAudio(attackAudio, 0,0.8f);
			isChangeGravity = true;
		}
	}
	if (CharactorManager::Instance()->GetSnake()->GetVelocity().length() < 4.0f)
	{
		CharactorManager::Instance()->GetSnake()->SwitchState("Basic");
	}
}

void PushHead::onExit()
{
	//CharactorManager::Instance()->GetSnake()->SetEnableResistance(false);
	isChangeGravity = false;
	
}
#pragma endregion

#pragma region BeamAttack
BeamAttack::BeamAttack()
{
	name = "BeamAttack";
}

void BeamAttack::onEnter()
{
	snake = CharactorManager::Instance()->GetSnake();
	Vector3 endPos = CharactorManager::Instance()->GetPlayer()->GetPos();
	Vector3 dir = (endPos - snake->GetPos()).normalize();
	Vector3 startPos = dir * startDis;
	beam = new Beam(endPos, startPos, CharactorManager::Instance()->GetPlayer());
	ObjectManager::Instance()->AddObjectBy(beam);
	Novice::PlayAudio(beamAudio,0,1.0f);
	attackTimer.restart();
	attackTimer.set_one_shot(true);
	attackTimer.set_wait_time(attackTime);
	attackTimer.set_on_timeout([&]()
		{
			snake->SwitchState("PushHead");
				
		});
}

void BeamAttack::onUpdate()
{
	Vector3 dir = (beam->GetPos() - snake->GetPos()).normalize();
	Vector3 startPos = snake->GetPos() +  dir * startDis;
	beam->SetStartPos(startPos);
	attackTimer.on_update(deltaTime);

}

void BeamAttack::onExit()
{
	beam->SetCanRemove(true);
	beam = nullptr;
	snake = nullptr;
}
#pragma endregion

#pragma region Chase
Chase::Chase()
{
	name = "Chase";
	chaseTimer.set_one_shot(true);
	chaseTimer.set_wait_time(chaseTime);
	chaseTimer.set_on_timeout([&]()
		{
			if (isAttack)
			{
				CharactorManager::Instance()->GetSnake()->SwitchState("Basic");
			}
			else
			{
				if (rand() % 100 < 10)
				{
					CharactorManager::Instance()->GetSnake()->SwitchState("Chase");
				}
				else
				{
					CharactorManager::Instance()->GetSnake()->SwitchState("Basic");
				}
			}
		});
}

void Chase::onEnter()
{
	chaseTimer.restart();
	target = CharactorManager::Instance()->GetPlayer();
	isAttack = false;


	CharactorManager::Instance()->GetSnake()->SwitchBehavior(Snake::SnakeBehavior::Smove);
}

void Chase::onUpdate()
{
	Vector3 dir = (target->GetPos() - CharactorManager::Instance()->GetSnake()->GetPos()).normalize();
	CharactorManager::Instance()->GetSnake()->SetToward(dir);
	//如果距离小于一定值，攻击
	if ((target->GetPos() - CharactorManager::Instance()->GetSnake()->GetPos()).length() < attakeRange)
	{
		CharactorManager::Instance()->GetSnake()->SwitchState("Attack");
	}



	chaseTimer.on_update(deltaTime);
}

void Chase::onExit()
{
	CharactorManager::Instance()->GetSnake()->SwitchBehavior(Snake::SnakeBehavior::Normol);
	target = nullptr;
}
#pragma endregion

Attack::Attack()
{
	name = "Attack";
	UpTimer.set_one_shot(true);
	UpTimer.set_wait_time(upTime);
	UpTimer.set_on_timeout([&]()
		{
			isAttack = true;
			CharactorManager::Instance()->GetSnake()->SetNodeEnableGravity(true);
			attackDir = (CharactorManager::Instance()->GetPlayer()->GetPos() - CharactorManager::Instance()->GetSnake()->GetPos()).normalize();
			CharactorManager::Instance()->GetSnake()->SetVelocity(attackDir * pushSpeed);

		});

	attackTimer.set_one_shot(true);
	attackTimer.set_wait_time(attackTime);
	attackTimer.set_on_timeout([&]()
		{

			if (rand() % 100 < 50)
			{
				CharactorManager::Instance()->GetSnake()->SwitchState("Chase");
			}
			else
			{
				CharactorManager::Instance()->GetSnake()->SwitchState("Basic");
			}
			//CharactorManager::Instance()->GetSnake()->SwitchState("Chase");
		});
		
}

void Attack::onEnter()
{
	UpTimer.restart();
	attackTimer.restart();
	isAttack = false;

	Vector2 toward = { CharactorManager::Instance()->GetSnake()->GetToward().x, CharactorManager::Instance()->GetSnake()->GetToward().y };


	

	startPos = CharactorManager::Instance()->GetSnake()->GetPos();
	upPos = CharactorManager::Instance()->GetSnake()->GetPos();
	upPos.z += upHeight;


}

void Attack::onUpdate()
{
	
	if (isAttack){

		attackTimer.on_update(deltaTime);
		if (!isSound)
		{
			if (CharactorManager::Instance()->GetSnake()->GetIsOnGround())
			{
				m_camera.Shake(4.0f, 0.2f);
				isSound = true;
				//播放音效
			}
		}
	
	}
	else
	{
		float t = UpTimer.get_progress();
		if (t > 1.0f)
		{
			t = 1.0f;
		}
		Vector3 pos;
		pos.x = (1 - t) * startPos.x + t * upPos.x;
		pos.y = (1 - t) * startPos.y + t * upPos.y;
		pos.z = (1 - t) * startPos.z + t * upPos.z;
		CharactorManager::Instance()->GetSnake()->SetPos(pos);


		UpTimer.on_update(deltaTime);
	}
}

void Attack::onExit()
{
	CharactorManager::Instance()->GetSnake()->SetNodeEnableGravity(false);
	isSound = false;

}

ToSecond::ToSecond()
{
	name = "ToSecond";
	timer.set_one_shot(true);
	timer.set_wait_time(totaltime);
	timer.set_on_timeout([&]()
		{

			CharactorManager::Instance()->GetSnake()->SwitchState("Jump");
			CharactorManager::Instance()->GetSnake()->phases = 1;
			CharactorManager::Instance()->GetSnake()->SetSpeed(4.0f);
			CharactorManager::Instance()->GetSnake()->SetNodeColor(0xb2444eFF);
		});
}

void ToSecond::onEnter()
{
	CharactorManager::Instance()->GetSnake()->SetNodeEnableGravity(true);
	timer.restart();
}

void ToSecond::onUpdate()
{
	timer.on_update(deltaTime);
}

void ToSecond::onExit()
{
	CharactorManager::Instance()->GetSnake()->SetNodeEnableGravity(false);
}

RangeAttack::RangeAttack()
{
	name = "RangeAttack";

	//初始化备选目标点
	firstPos = { -600.0f,300.0f};

}

void RangeAttack::onEnter()
{
	//重复15次
	for (int i = 0; i < 15; i++)
	{
		//随机从0到4行选一行
		int row = rand() % 5;
		//随机从0到6列选一列
		int col = rand() % 7;
		Vector2 targetPos = { firstPos.x + col * perSize.x,firstPos.y - row * perSize.y };
	}


}

void RangeAttack::onUpdate()
{
}

void RangeAttack::onExit()
{
}
