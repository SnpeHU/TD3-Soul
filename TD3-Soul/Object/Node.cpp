#include "Node.h"

Node::Node(Vector3 pos)
{
	this->pos = pos;
	size = { 30.0f,30.0f };
	drawPos = { 0.0f,size.y };
	color = 0x9E5C62FF;
	bordercolor = 0x8E5C62FF;
	boderwidth = 3;

	isEnableGravity = false;
	gravity = 0.2f;

	hurt_box = CollisionManager::Instance()->CreatCollisionBox(this);
	hurt_box->setLayerSrc(CollisionLayer::Enemy);
	hurt_box->addLayerDest(CollisionLayer::PlayerBullet, [this]() {
		if (isCanHurt)
		{
			hurt_box->setEnabled(false);
			isDestroyed = true;
		}
		});

	hurtBoxSize = { size.x * 2 - size.x/4,size.y };
	hurt_box->setSize(hurtBoxSize);


}

void Node::Update()
{
	shadowSize = { (size.x + 8) * (1.0f - pos.z * 0.003f), (size.y - 5) * (1.0f - pos.z * 0.003f) };//影子大小更新
	Charactor::Update();
	if(!isDestroyed)
	{
		if (pos.z > 40.0f)
		{
			hurt_box->setEnabled(false);
		}
		else
		{
			hurt_box->setEnabled(true);
		}
	}


}

void Node::Draw(const Camera& camera)
{
	if (!isDestroyed)
	{
		Object::Draw(camera);
		//Charactor::Draw(camera);
		Vector2 screenDrawPos = Transform(drawPos, objectMatrix);
		Novice::DrawEllipse(int(screenDrawPos.x), int(screenDrawPos.y - pos.z * camera.heightscale), int(size.x), int(size.y), 0.0f, color, kFillModeSolid);
		//渲染边框
		//for (int i = 0; i < boderwidth; i++)
		//{
		//	Novice::DrawEllipse(int(screenDrawPos.x), int(screenDrawPos.y - pos.z * camera.heightscale), int(size.x + i), int(size.y + i), 0.0f, bordercolor, kFillModeWireFrame);
		//}
	}



}
