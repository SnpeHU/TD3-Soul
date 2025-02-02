#include "Wall.h"

Wall::Wall(Vector3 pos, Vector3 size)
{
	this->pos = pos;
	this->size.x = size.x;
	this->size.y = size.y;

	height = size.z;//返す言葉もない


	color = 0x413D32FF;//前方墙体颜色
	topColor = 0x4E4B3EFF;
	name = "Wall";
	//collisionbox
	hurt_box = CollisionManager::Instance()->CreatCollisionBox(this);
	hurt_box->setLayerSrc(CollisionLayer::Map);
	hurt_box->addLayerDest(CollisionLayer::Player, [this]() {
		});
	hurt_box->addLayerDest(CollisionLayer::PlayerBullet, [this]() {
		});
	hurt_box->addLayerDest(CollisionLayer::Enemy, [this]() {
		});
	hurt_box->addLayerDest(CollisionLayer::EnermyBullet, [this]() {
		});
	hurtBoxSize = { size.x,size.y };
	hurt_box->setSize(hurtBoxSize);
	
	//hurt_box->setPos(Vector3(pos.x, pos.y - hurtBoxSize.y / 2, pos.z));
	hurt_box->setPos(Vector3(pos.x, pos.y + hurtBoxSize.y / 2, pos.z));
}

void Wall::Update()
{
}

void Wall::Draw(const Camera& camera)
{
	Object::Draw(camera);
	//Vector2 frontDrawPos = TransformFrom3D(Vector3(-size.x/2, -size.y,height), objectMatrix,camera.heightscale);
	//Vector2 topDrawPos = TransformFrom3D(Vector3(-size.x / 2, 0.0f, height), objectMatrix, camera.heightscale);
	Vector2 frontDrawPos = TransformFrom3D(Vector3(-size.x / 2,0.0f, height), objectMatrix, camera.heightscale);
	Vector2 topDrawPos = TransformFrom3D(Vector3(-size.x / 2,size.y, height), objectMatrix, camera.heightscale);

	Novice::DrawBox(int(frontDrawPos.x), int(frontDrawPos.y), int(size.x), int(height/2), 0.0f, color, kFillModeSolid);
	Novice::DrawBox(int(topDrawPos.x), int(topDrawPos.y), int(size.x), int(size.y), 0.0f, topColor, kFillModeSolid);
	
}
