#include "Beam.h"
#include "Manager/CharactorManager.h"
Beam::Beam(Vector3 _endPos, Vector3 _startPos)
{
	this->pos = _endPos;//光束落点位置
	this->startPos = _startPos;//光束发射位置
	size = { 10.0f,10.0f };
	color = 0x8B3A3AFF;

	speed = 3.0f;
}

void Beam::Update()
{
	//计算落点位置与玩家位置的方向
	Vector3 playerPos = CharactorManager::Instance()->GetPlayer()->GetPos();
	Vector3 dir = (playerPos - pos).normalize();
	velocity = dir * speed;

	Bullet::Update();
}

void Beam::Draw(const Camera& camera)
{
	Object::Draw(camera);
	Vector2 startScreenPos = TransformFrom3D(startPos, objectMatrix, camera.heightscale);
	Vector2 endScreenPos = TransformFrom3D(pos, objectMatrix, camera.heightscale);
	Novice::DrawLine(int(startScreenPos.x), int(startScreenPos.y), int(endScreenPos.x), int(endScreenPos.y), color);
	/*Novice::Dra*/
}
	
	
