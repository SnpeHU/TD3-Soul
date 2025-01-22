#include "Bullet.h"


Bullet::Bullet(Vector3 pos)
{
	this->pos = pos;
	size = { 10.0f,10.0f };
	name = "Bullet";
}
void Bullet::Update()
{
}

void Bullet::Draw(const Camera& camera)
{
	(void)camera;
}
