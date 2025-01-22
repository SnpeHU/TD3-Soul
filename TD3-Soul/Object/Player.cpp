#include "Player.h"
#include "Novice.h"
#ifdef _DEBUG
#include<imgui.h>
#endif // DEBUG
Player::Player()
{
	pos = { 0.0f,0.0f ,0.0f};
	toward = { 0.0f,0.0f ,0.0f};
	size = { 32.0f,32.0f };
	speed = 3.0f;

	leftTop = { -size.x / 2,size.y };
	

	isDeBug = true;

	name = "Player";
}

Player::Player(Vector3 _pos)
{
	pos = _pos;
	toward = { 0.0f,0.0f ,0.0f};
	size = { 40.0f,40.0f };
	speed = 3.0f;


	leftTop = { -size.x / 2,size.y };

	shadowColor = 0x00868B60;
	shadowSize = { size.x/2 + 10,size.y/2 - 5 };


	isDeBug = true;
	name = "Player";

	//bullets
	hurt_box = CollisionManager::Instance()->CreatCollisionBox(this);
	hurt_box->setLayerSrc(CollisionLayer::Player);
	hurt_box->addLayerDest(CollisionLayer::Map, [this]() {
		});
	hurt_box->addLayerDest(CollisionLayer::Enemy, [this]() {
		});
	hurtBoxSize = { size.x,size.y };
	hurt_box->setSize(hurtBoxSize);
}

void Player::Input(char* keys, char* prekeys)
{
	(void)keys;
	(void)prekeys;
	if (keys[DIK_W])
	{
		isUp = true;
	}
	else
	{
		isUp = false;
	}
	if (keys[DIK_S])
	{
		isDown = true;
	}
	else
	{
		isDown = false;
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

	if (keys[DIK_SPACE])
	{
		isJumpButton = true;
	}
	else
	{
		isJumpButton = false;
	}




}

void Player::Update()
{

	Vector3 dir = { float(isRight - isLeft),float(isUp - isDown) ,0.0f};
	toward = dir.normalize();
	velocity = toward * speed;
	




	if (isJumpButton && isOnGround)
	{
		acceleration.z = jumpForce;
	}	

	
	shadowSize = { (size.x / 2 + 8) * (1.0f - pos.z * 0.005f), (size.y / 2 - 5) * (1.0f - pos.z * 0.005f) };
	Charactor::Update();


}

void Player::Draw(const Camera& camera)
{
	
	Object::Draw(camera);
	//Vector2 screenleftTop = TransformFrom3D(Vector3(leftTop.x,leftTop.y,pos.z), objectMatrix,camera.heightscale);
	Vector2 screenleftTop = Transform(leftTop, objectMatrix);
	//Charactor::Draw(camera);
	Novice::DrawBox(int(screenleftTop.x), int(screenleftTop.y - pos.z * camera.heightscale), int(size.x), int(size.y), 0.0f, bodycolor, kFillModeSolid);
	

	if (isDeBug)
	{
		//Object::DrawDebug(camera);
		ImGui::Begin("Player");
		ImGui::Text("pos: %.2f %.2f %.2f", pos.x, pos.y,pos.z);
		ImGui::Text("toward: %.2f %.2f %.2f", toward.x, toward.y, toward.z);
		
		ImGui::Text("velocity: %.2f %.2f %.2f", velocity.x, velocity.y, velocity.z);

		//ImGui::DragFloat("height", &height, 0.1f, 0.0f, 100.0f);
		ImGui::DragFloat("gravity", &gravity, 0.1f, 0.0f, 2.0f);
		ImGui::DragFloat("jumpForce", &jumpForce, 0.1f, 0.0f, 100.0f);
		ImGui::End();
	}
}

void Player::ClearNodes()
{

}
