#include "Charactor.h"
#include "Novice.h"
//Charactor::Charactor()
//{
//	pos = { 0.0f,0.0f };
//	toward = {1.0f,0.0f};
//	size = { 20.0f,20.0f };
//	speed = 3.0f;
//	color = WHITE;
//
//	leftTop = { -size.x / 2,size.y };
//
//
//	isDeBug = true;
//
//}
void Charactor::Input(char* keys, char* prekeys)
{
	(void)keys;
	(void)prekeys;

}
void Charactor::Update()
{
	if (isOnGround)
	{
		if (isEnableResistance)
		{
			acceleration.x = velocity.x * (-kResistance);
			acceleration.y = velocity.y * (-kResistance);
		}
	}

	if (isEnableGravity)
	{
		acceleration.z -= gravity;
	}

	//if (acceleration.length() < 0.001f)
	//{
	//	acceleration.x = 0.0f;
	//	acceleration.y = 0.0f;
	//	acceleration.z = 0.0f;
	//}

	velocity += acceleration;

	if (velocity.length() < 0.05f)
	{
		velocity.x = 0;
		velocity.y = 0;
		velocity.z = 0;
	}


	pos += velocity;

	


	if (pos.z <= 0.0f)
	{
		pos.z = 0.0f;
		velocity.z = 0.0f;
		acceleration.z = 0.0f;
		isOnGround = true;
	}
	else
	{
		isOnGround = false;
	}
	if (hurt_box)
	{
		hurt_box->setPos(get_logic_center());
	}
	
	if (shadowSize.x < 0.0f)
	{
		shadowSize.x = 0.0f;
	}
	if (shadowSize.y < 0.0f)
	{
		shadowSize.y = 0.0f;
	}
}
void Charactor::Draw(const Camera& camera)
{

	(void)camera;
}


void Charactor::SwitchState(const std::string& _id)
{
	stateMachine.SwitchTo(_id);
}