#include "ButtonWall.h"
#include <cstdint>
ButtonWall::ButtonWall(Vector3 pos, Vector3 size)
{
	this->pos = pos;
	this->size.x = size.x;
	this->size.y = size.y;

	height = size.z;//返す言葉もない


	color = 0x413D32FF;//前方墙体颜色
	topColor = 0x4E4B3EFF;
	originTopColor = topColor;
	name = "ButtonWall";
	//collisionbox
	hurt_box = CollisionManager::Instance()->CreatCollisionBox(this);
	hurt_box->setLayerSrc(CollisionLayer::Map);
	hurt_box->addLayerDest(CollisionLayer::PlayerBullet, [this]() {
		if (onTrigger)
		{
			onTrigger();
			Novice::PlayAudio(stoneAudio,0,2.0f);
			return;
		}
		});
	hurt_box->addLayerDest(CollisionLayer::Player, [this]() {
		});
	hurtBoxSize = { size.x,size.y };
	hurt_box->setSize(hurtBoxSize);

	//hurt_box->setPos(Vector3(pos.x, pos.y - hurtBoxSize.y / 2, pos.z));
	hurt_box->setPos(Vector3(pos.x, pos.y + hurtBoxSize.y / 2, pos.z));


	colorChangeTimer.set_one_shot(false);
	colorChangeTimer.set_wait_time(colorChangeTime);
	colorChangeTimer.set_on_timeout([&]() {

		int temp = tipColor;

		tipColor = originTopColor;
		originTopColor = temp;
		});

	imgPos = { -size.x + 20 ,size.y + 50};

	rotateCenter = { pos.x,pos.y + size.y / 2,pos.z + height+32};
	corners[0] = { -64 / 2,64 /2 };
	corners[1] = { 64 / 2,64 / 2 };
	corners[2] = { -64/ 2,-64 / 2 };
	corners[3] = { 64 / 2,-64 / 2 };

}

void ButtonWall::Update()
{
    
	colorChangeTimer.on_update(deltaTime);
    // 颜色插值函数
	float t = colorChangeTimer.get_progress();
	if (t > 1.0f)
	{
		t = 1.0f;
	}
	topColor = LerpColor(originTopColor, tipColor, t);


	float moveOffset = sin(MoveTime * 3) * moveRange;
	MoveTime += deltaTime;
	offset = moveOffset;


	if (isRotate)
	{
		rotate += rotateSpeed;
	}


}

void ButtonWall::Draw(const Camera& camera)
{
	Wall::Draw(camera);
	if (!isRotate)
	{
		Vector2 imgDrawPos = Transform(imgPos, objectMatrix);
		Novice::DrawSprite(int(imgDrawPos.x), int(imgDrawPos.y + offset), img, 1.0f, 1.0f, 0.0f, WHITE);
	}
	else
	{
		Matrix3x3 rotateCenterMatrix = camera.GetObjectMatrix(Vector2(rotateCenter.x, rotateCenter.y),rotate);

		Vector2 screenDrawPos[4];
		for (size_t i = 0; i < 4; i++)
		{
			screenDrawPos[i] = Transform(corners[i], rotateCenterMatrix);
		}

		for (int i = 0; i < 11; i++)
		{
			Novice::DrawQuad(int(screenDrawPos[0].x), int(screenDrawPos[0].y - (i * 2) - rotateCenter.z * camera.heightscale + +offset),
				int(screenDrawPos[1].x), int(screenDrawPos[1].y - (i * 2) - rotateCenter.z * camera.heightscale + offset),
				int(screenDrawPos[2].x), int(screenDrawPos[2].y - (i * 2) - rotateCenter.z * camera.heightscale + offset),
				int(screenDrawPos[3].x), int(screenDrawPos[3].y - (i * 2) - rotateCenter.z * camera.heightscale + offset),
				i * 64, 0, 64, 64, img
				, WHITE);
		}
	}
}
	

uint32_t ButtonWall::LerpColor(uint32_t startColor, uint32_t endColor, float t)
{
	uint8_t startA = (startColor >> 24) & 0xFF;
	uint8_t startR = (startColor >> 16) & 0xFF;
	uint8_t startG = (startColor >> 8) & 0xFF;
	uint8_t startB = startColor & 0xFF;

	uint8_t endA = (endColor >> 24) & 0xFF;
	uint8_t endR = (endColor >> 16) & 0xFF;
	uint8_t endG = (endColor >> 8) & 0xFF;
	uint8_t endB = endColor & 0xFF;

	uint8_t resultA = static_cast<uint8_t>(startA + t * (endA - startA));
	uint8_t resultR = static_cast<uint8_t>(startR + t * (endR - startR));
	uint8_t resultG = static_cast<uint8_t>(startG + t * (endG - startG));
	uint8_t resultB = static_cast<uint8_t>(startB + t * (endB - startB));

	return (resultA << 24) | (resultR << 16) | (resultG << 8) | resultB;
}

void ButtonWall::SetOnTrigger(std::function<void()> _onTrigger)
{
	onTrigger = _onTrigger;
}
