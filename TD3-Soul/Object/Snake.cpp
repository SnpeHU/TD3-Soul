#include "Snake.h"
#include "Novice.h"
#include "State/SnakeState.h"
#include "Manager/CharactorManager.h"
#include "Emitter/BlockParticle.h"
#ifdef _DEBUG
#include<imgui.h>
#endif // DEBUG
Snake::Snake(Vector3 pos)
{
	this->pos = pos;
	toward = { 1.0f,0.0f ,0.0f};
	size = { 30.0f,30.0f };
	speed = 2.5f;
	color = 0x9E5C62FF;
	nodeNum = 3;
	nodeInterval = 45.0f;
	aliveNodeNum = nodeNum;
	gravity = 0.05f;
	//headPos = { 0.0f,size.y / 2 };

	//spine = Chain(pos, nodeNum, nodeInterval, 2* M_PI, 2 * M_PI);
	spine = Chain(pos, nodeNum, nodeInterval, M_PI, M_PI);

	spine.joints[0]->SetSize({ 35.0f,35.0f });
	spine.joints[0]->isHead = true;
	spine.joints[2]->isHeart = true;
	//spine = Chain(pos, nodeNum, nodeInterval, M_PI/2, M_PI/2);

	isEnableGravity = false;
	kResistance = 0.02f;
	isDeBug = true;

	name = "Snake";

	//collisionbox
	hurt_box = CollisionManager::Instance()->CreatCollisionBox(this);
	hurt_box->setLayerSrc(CollisionLayer::Enemy);

	hurtBoxSize = { size.x * 2 - size.x / 4,size.y };
	hurt_box->setSize(hurtBoxSize);

	//stateMachine
	stateMachine.RegisterState("Basic", new BasicState());
	stateMachine.RegisterState("Jump", new JumpState());
	stateMachine.RegisterState("Move", new MoveState());//逃离
	stateMachine.RegisterState("CircleMove", new CircleMove());
	stateMachine.RegisterState("UpHead",new UpHead());
	stateMachine.RegisterState("PushHead", new PushHead());
	stateMachine.RegisterState("BeamAttack", new BeamAttack());
	stateMachine.RegisterState("Chase", new Chase());
	stateMachine.RegisterState("Attack", new Attack());
	stateMachine.RegisterState("ToSecond",new ToSecond());
	stateMachine.SetEntry("Basic");


	invincibleTimer.set_one_shot(true);
	invincibleTimer.set_wait_time(invincibleTime);
	invincibleTimer.set_on_timeout([this]() {
		isInvincible = false;
		invincibleTimer.restart();
		});

}

Snake::~Snake()
{
	ClearNodes();
}


void Snake::Input(char* keys, char* prekeys)
{
	(void)prekeys;
	if (keys[DIK_W])
	{
		isForward = true;
	}
	else
	{
		isForward = false;
	}
	if (keys[DIK_S])
	{
		isBack = true;
	}
	else
	{
		isBack = false;
	}
	if (keys[DIK_A])
	{
		isLeft = true;
	}
	else
	{
		isLeft = false;
	}
	if (keys[DIK_D])
	{
		isRight = true;
	}
	else
	{
		isRight = false;
	}

	if(keys[DIK_Q])
	{
		isUp = true;
	}
	else
	{
		isUp = false;
	}

	if (keys[DIK_E])
	{
		isDown = true;
	}
	else
	{
		isDown = false;
	}

}

void Snake::Update()
{
	if (isDead)
	{
		return;
	}
	//Vector3 dir = {float(isRight - isLeft), float(isForward - isBack) ,float(isUp - isDown)};
	//if (dir.x != 0 || dir.y != 0 || dir.z !=0)
	//{
	//	dir = dir.normalize();
	//	toward = dir;
	//	velocity = dir * speed;
	//}
	//else
	//{
	//	velocity = { 0.0f,0.0f,0.0f };
	//}
	float sMoveOffset = sin(sMoveTime * speed) * moveRange;
	switch (curBehavior)
	{
	case Snake::SnakeBehavior::OnInput:
		break;
	case Snake::SnakeBehavior::Smove:
		sMoveTime += deltaTime;
		if (sMoveTime > 100 * M_PI)
		{
			sMoveTime = 0.0f;
		}

		//Vector3 offset = { -toward.y, toward.x, 0.0f };
		pos.x += sMoveOffset * -toward.y;
		pos.y += sMoveOffset * toward.x;
		
		velocity = toward * speed;

		break;
	case Snake::SnakeBehavior::Normol:
		toward = velocity.normalize();
		break;
	default:
		break;
	}
	

	if (CharactorManager::Instance()->GetPlayer())
	{
		if (isActive && !isDead)
		{
		//	stateMachine.onUpdate();
		}
		else
		{
			//if(!CharactorManager::Instance()->GetPlayer()->GetIsDead())
			//{
			//	isActive = true;
			//}
		}
		
	}

	if (isInvincible)
	{
		invincibleTimer.on_update(deltaTime);
	}


	spine.resolve(pos, toward);
	spine.upDateCanHurt();

	if (aliveNodeNum < 3)
	{
		isDead = true;
		for (int i = 0; i < 100; i++)
		{
			Vector3 parPos = { pos.x + rand() % int(size.x) - size.x / 2,pos.y + rand() % int(size.y) - size.y / 2,pos.z };
			Vector3 acc = { 0.0f,0.0f,float(rand() % 10 /2) };

			float lifeTime = float(rand() % 100) / 100.0f + 1.0f;

			float pspeed = 0.0f;
			float rotateSpeed = 0.0f;
			int pcolor = color;
			auto newBlockParticle = std::make_unique<BlockParticle>(parPos, Vector2(5, 5), toward, acc, pspeed, lifeTime, rotateSpeed, pcolor);
			ObjectManager::Instance()->AddObject(std::move(newBlockParticle));
		}
	}


	Charactor::Update();
	 

	
}

void Snake::Draw(const Camera& camera)
{
	Object::Draw(camera);

#ifdef _DEBUG
	ImGui::Begin("Snake");
	ImGui::Text("pos: %.2f %.2f %.2f", pos.x, pos.y, pos.z);
	ImGui::Text("toward: %.2f %.2f %.2f", toward.x, toward.y,toward.z);
	ImGui::Text("velocity: %.2f %.2f %.2f", velocity.x, velocity.y, velocity.z);
	ImGui::Text("acceleration: %.2f %.2f %.2f", acceleration.x, acceleration.y, acceleration.z);
	ImGui::Text("isOnGround: %d", isOnGround);
	ImGui::Text("isEnableGravity: %d", isEnableGravity);
	ImGui::Text("isEnableResistance: %d", isEnableResistance);
	ImGui::Text("isInvincible: %d", isInvincible);

	ImGui::Text("isDead: %d", isDead);
	ImGui::DragFloat("pos.x", &pos.x, 1.0f, -800.0f, 800.0f);
	ImGui::DragFloat("pos.y", &pos.y, 1.0f, -600.0f, 600.0f);
	ImGui::DragFloat("pos.z", &pos.z, 1.0f, 0.0f, 600.0f);
	ImGui::Text("currentState: %s", stateMachine.GetCurrentState().c_str());

	//ImGui::DragFloat("jumpForce", &jumpForce, 0.1f, 0.0f, 100.0f);
	ImGui::End();

#endif
	
}

void Snake::SwitchBehavior(SnakeBehavior behavior)
{
	curBehavior = behavior;
	sMoveTime = 0.0f;
}

void Snake::Reset(Vector3 _pos)
{
	this->pos = _pos;
	toward = { 1.0f,0.0f ,0.0f };
	velocity = { 0.0f,0.0f,0.0f };
	acceleration = { 0.0f,0.0f,0.0f };
	stateMachine.SwitchTo("Basic");
	speed = 3.0f;
	ClearNodes();
	//headPos = { 0.0f,size.y / 2 };
	spine = Chain(pos, nodeNum, nodeInterval, 2 * M_PI, 2 * M_PI);
	isDead = false;
	isInvincible = false;
	invincibleTimer.restart();
	aliveNodeNum = nodeNum;
	spine.joints[0]->SetSize({ 35.0f,35.0f });
	spine.joints[0]->isHead = true;
	spine.joints[2]->isHeart = true;
}

void Snake::SetNodeEnableGravity(bool flag)
{
	isEnableGravity = flag;
	spine.SetEnableGravity(flag);
}

void Snake::SetNodeColor(int _color)
{
	for (auto& joint : spine.joints)
	{
		joint->SetColor(_color);
	}
}

void Snake::ClearNodes()
{

	for (auto& joint : spine.joints) {
		ObjectManager::Instance()->RemoveObject(joint);
	}
	spine.joints.clear();
	
}


void Snake::SetAngleConstraint(float azimuthalConstraint, float polarConstraint)
{
	//调整链条的角度约束
	spine.azimuthalConstraint = azimuthalConstraint;
	spine.polarConstraint = polarConstraint;
}

//void Snake::JumpTo(Vector3 targetPos)
//{
//
//}
