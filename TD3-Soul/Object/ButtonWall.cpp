#include "ButtonWall.h"

ButtonWall::ButtonWall(Vector3 pos, Vector3 size)
{
	this->pos = pos;
	this->size.x = size.x;
	this->size.y = size.y;

	height = size.z;//返す言葉もない


	color = 0x413D32FF;//前方墙体颜色
	topColor = 0x4E4B3EFF;
	name = "ButtonWall";
	//collisionbox
	hurt_box = CollisionManager::Instance()->CreatCollisionBox(this);
	hurt_box->setLayerSrc(CollisionLayer::Map);
	hurt_box->addLayerDest(CollisionLayer::PlayerBullet, [this]() {
		if (onTrigger)
		{
			onTrigger();
			return;
		}
		});
	hurt_box->addLayerDest(CollisionLayer::Player, [this]() {
		});
	hurtBoxSize = { size.x,size.y };
	hurt_box->setSize(hurtBoxSize);

	//hurt_box->setPos(Vector3(pos.x, pos.y - hurtBoxSize.y / 2, pos.z));
	hurt_box->setPos(Vector3(pos.x, pos.y + hurtBoxSize.y / 2, pos.z));
}

void ButtonWall::Update()
{
}

void ButtonWall::Draw(const Camera& camera)
{
	Wall::Draw(camera);
}

void ButtonWall::SetOnTrigger(std::function<void()> _onTrigger)
{
	onTrigger = _onTrigger;
}
