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
	if (isEnableGravity)
	{
		acceleration.z -= gravity;
	}
	velocity.z += acceleration.z;
	pos += velocity;

	


	if (pos.z <= 0.0f)
	{
		pos.z = 0.0f;
		velocity.z = 0.0f;
		isOnGround = true;
	}
	else
	{
		isOnGround = false;
	}

	hurt_box->setPos(get_logic_center());
	
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
	Vector2 screenPos = Transform(Vector2(0, 0), objectMatrix);
	


	
	
}


void Charactor::SwitchState(const std::string& _id)
{
	stateMachine.SwitchTo(_id);
}