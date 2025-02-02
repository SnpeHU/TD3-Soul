#include "Bullet.h"

void Bullet::Update()
{
	velocity += acceleration;
	if (velocity.length() < 0.05f)
	{
		velocity.x = 0;
		velocity.y = 0;
		velocity.z = 0;
	}
	pos += velocity;
	if (hurt_box)
	{
		hurt_box->setPos(get_logic_center());
	}
}
