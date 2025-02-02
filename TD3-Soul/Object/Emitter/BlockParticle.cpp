#include "BlockParticle.h"

BlockParticle::BlockParticle(Vector3 pos, Vector3 toward, float lifeTime)
{
	name = "BlockParticle";
	this->pos = pos;
	this->toward = toward;
	this->lifeTime = lifeTime;
	
	speed = 3.0f;
	velocity = toward * speed;

	acceleration = { 0.0f,0.0f,-0.1f };

	size = { 15.0f,15.0f };
	color = 0x8B3A3AFF;

	lifeTimer.set_one_shot(true);
	lifeTimer.set_wait_time(lifeTime);
	lifeTimer.set_on_timeout([this]() {
		isCanRemove = true;

		});

	//leftTop = { -size.x / 2,size.y };

}

BlockParticle::BlockParticle(Vector3 pos, Vector2 size, Vector3 toward, Vector3 acceleration, float speed, float lifeTime, int color,float sizeSpeed)
{
	name = "BlockParticle";
	this->pos = pos;
	this->toward = toward;
	this->lifeTime = lifeTime;
	this->size = size;
	this->speed = speed;
	this->sizeSpeed = sizeSpeed;
	this->acceleration = acceleration;
	this->color = color;
	lifeTimer.set_one_shot(true);
	lifeTimer.set_wait_time(lifeTime);
	lifeTimer.set_on_timeout([this]() {
		isCanRemove = true;
		});
	//leftTop = { -size.x / 2,size.y };
	corners[0] = { -size.x / 2,size.y };
	corners[1] = { size.x / 2,size.y };
	corners[2] = { -size.x / 2,0.0f };
	corners[3] = { size.x / 2,0.0f };
}



void BlockParticle::Update()
{
	lifeTimer.on_update(deltaTime);
	size += sizeSpeed;
	//leftTop = { -size.x / 2,size.y };
	corners[0] = { -size.x / 2,size.y };
	corners[1] = { size.x / 2,size.y };
	corners[2] = { -size.x / 2,0.0f };
	corners[3] = { size.x / 2,0.0f };

	velocity = toward * speed;
	velocity += acceleration;
	pos += velocity;

	//随时间逐渐变淡
	color = (color & 0xFFFFFF00) | (int(255 * (1 -lifeTimer.get_progress())));
}

void BlockParticle::Draw(const Camera& camera)
{
	objectMatrix = camera.GetObjectMatrix(Vector2(pos.x, pos.y),1.0f);
	//Vector2 screenDrawPos = Transform(leftTop, objectMatrix);
	Vector2 screenDrawPos[4];

	//Novice::DrawBox(int(screenDrawPos.x), int(screenDrawPos.y - pos.z * camera.heightscale), int(size.x), int(size.y), 0.0f, color, kFillModeSolid);
	for (int i = 0; i < 3; i++)
	{
		screenDrawPos[i] = Transform(corners[i], objectMatrix);
	}

	Novice::DrawQuad(int(screenDrawPos[0].x), int(screenDrawPos[0].y -pos.z * camera.heightscale),
					int(screenDrawPos[1].x), int(screenDrawPos[1].y -pos.z * camera.heightscale),
					int(screenDrawPos[2].x), int(screenDrawPos[2].y -pos.z * camera.heightscale),
					int(screenDrawPos[3].x), int(screenDrawPos[3].y -pos.z * camera.heightscale),
					0,0,0,0,0
					, color);
	

}
