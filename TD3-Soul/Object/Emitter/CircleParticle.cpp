#include "CircleParticle.h"

CircleParticle::CircleParticle(Vector3 pos, float lifeTime, float speed)
{
	this->pos = pos;
	this->lifeTime = lifeTime;
	this->speed = speed;
	velocity = { 0.0f,0.0f,0.0f };
	acceleration = { 0.0f,0.0f,0.0f };
	size = { 0.0f,0.0f };
	color = 0x696969FF;
	lifeTimer.set_one_shot(true);
	lifeTimer.set_wait_time(lifeTime);
	lifeTimer.set_on_timeout([this]() {
		isCanRemove = true;
		});
}

void CircleParticle::Update()
{
	lifeTimer.on_update(deltaTime);
	size.x += speed;
	size.y += speed * 0.8f;


}

void CircleParticle::Draw(const Camera& camera)
{
	Matrix3x3 cameraMatrix = camera.GetCameraMatrix();
	Vector2 screenDrawPos = TransformFrom3D(pos, cameraMatrix, camera.heightscale);
	Novice::DrawEllipse(int(screenDrawPos.x), int(screenDrawPos.y), int(size.x), int(size.y), 0.0f, color, kFillModeWireFrame);
}
