#include "BlockParticle.h"

BlockParticle::BlockParticle(Vector3 pos, Vector3 toward, float lifeTime)
{
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

	leftTop = { -size.x / 2,size.y };

}

void BlockParticle::Update()
{
	lifeTimer.on_update(deltaTime);
	velocity = toward * speed;
	velocity += acceleration;
	pos += velocity;

	//随时间逐渐变淡
	//color = (color & 0xFFFFFF00) | (int(255 * lifeTimer.get_progress()));
	color = GetColor(139, 58, 58, int(255 * (1 - lifeTimer.get_progress())));
}

void BlockParticle::Draw(const Camera& camera)
{
	objectMatrix = camera.GetObjectMatrix(Vector2(pos.x, pos.y),0.0f);
	Vector2 screenDrawPos = Transform(leftTop, objectMatrix);

	Novice::DrawBox(int(screenDrawPos.x), int(screenDrawPos.y - pos.z * camera.heightscale), int(size.x), int(size.y), 0.0f, color, kFillModeSolid);
	

}
