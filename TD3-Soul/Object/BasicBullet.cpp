#include "BasicBullet.h"

BasicBullet::BasicBullet(Vector3 pos,Vector3 toward,float speed)
{
	this->pos = pos;
	this->toward = toward;
	this->speed = speed;

	size = { 10.0f,10.0f };

	color = 0x8B3A3AFF;

	hurt_box = CollisionManager::Instance()->CreatCollisionBox(this);
	hurt_box->setLayerSrc(CollisionLayer::EnermyBullet);
	hurt_box->addLayerDest(CollisionLayer::Map, [this]() {
		isCanRemove = true;
		});
	hurt_box->addLayerDest(CollisionLayer::Player, [this]() {
		isCanRemove = true;
		});
	hurtBoxSize = { size.x * 2 - 3,size.y * 2 - 3 };
	hurt_box->setSize(hurtBoxSize);
}

void BasicBullet::Update()
{
	velocity = toward * speed;
	Bullet::Update();
}

void BasicBullet::Draw(const Camera& camera)
{
	Object::Draw(camera);
	Vector2 screenDrawPos = Transform(Vector2(0.0f, size.y), objectMatrix);
	Novice::DrawEllipse(int(screenDrawPos.x), int(screenDrawPos.y - pos.z * camera.heightscale), int(size.x), int(size.y), 0.0f, color, kFillModeSolid);
}
