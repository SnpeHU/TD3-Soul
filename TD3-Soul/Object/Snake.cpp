#include "Snake.h"
#include "Novice.h"
#include "State/SnakeState.h"
#include "Manager/CharactorManager.h"
#ifdef _DEBUG
#include<imgui.h>
#endif // DEBUG
Snake::Snake(Vector3 pos)
{
	this->pos = pos;
	toward = { 1.0f,0.0f ,0.0f};
	size = { 20.0f,20.0f };
	speed = 3.0f;
	color = 0x4E7A70FF;
	nodeNum = 10;
	nodeInterval = 40.0f;

	//headPos = { 0.0f,size.y / 2 };

	spine = Chain(pos, nodeNum, nodeInterval, 2* M_PI, 2 * M_PI);


	isEnableGravity = false;
	kResistance = 0.02f;
	isDeBug = true;

	name = "Snake";

	//collisionbox
	hurt_box = CollisionManager::Instance()->CreatCollisionBox(this);
	hurt_box->setLayerSrc(CollisionLayer::Enemy);
	//hurt_box->addLayerDest(CollisionLayer::Map, [this]() {
	//	});
	//hurt_box->addLayerDest(CollisionLayer::Player, [this]() {
	//	});
	hurtBoxSize = { size.x * 2 - size.x / 4,size.y };
	hurt_box->setSize(hurtBoxSize);

	//stateMachine
	stateMachine.RegisterState("Basic", new BasicState());
	stateMachine.RegisterState("Jump", new JumpState());
	stateMachine.RegisterState("Move", new MoveState());
	stateMachine.RegisterState("CircleMove", new CircleMove());
	stateMachine.RegisterState("UpHead",new UpHead());
	stateMachine.RegisterState("PushHead", new PushHead());
	stateMachine.RegisterState("BeamAttack", new BeamAttack());
	stateMachine.SetEntry("Basic");



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



	if (CharactorManager::Instance()->GetPlayer())
	{
		if (isActive)
		{
			stateMachine.onUpdate();
		}
		
	}



	spine.resolve(pos, toward);
	spine.upDateCanHurt();


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
	ImGui::DragFloat("pos.x", &pos.x, 1.0f, -800.0f, 800.0f);
	ImGui::DragFloat("pos.y", &pos.y, 1.0f, -600.0f, 600.0f);
	ImGui::DragFloat("pos.z", &pos.z, 1.0f, 0.0f, 600.0f);
	ImGui::Text("currentState: %s", stateMachine.GetCurrentState().c_str());

	//ImGui::DragFloat("jumpForce", &jumpForce, 0.1f, 0.0f, 100.0f);
	ImGui::End();

#endif
	
}

void Snake::Reset(Vector3 _pos)
{
	this->pos = _pos;
	toward = { 1.0f,0.0f ,0.0f };
	velocity = { 0.0f,0.0f,0.0f };
	acceleration = { 0.0f,0.0f,0.0f };
	stateMachine.SwitchTo("Basic");
	ClearNodes();
	//headPos = { 0.0f,size.y / 2 };
	spine = Chain(pos, nodeNum, nodeInterval, 2 * M_PI, 2 * M_PI);
	isDead = false;
}

void Snake::SetNodeEnableGravity(bool flag)
{
	spine.SetEnableGravity(flag);
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
