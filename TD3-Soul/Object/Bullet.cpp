#include "Bullet.h"

void Bullet::Update()
{
	velocity += acceleration;
	pos += velocity;
	if (hurt_box)
	{
		hurt_box->setPos(get_logic_center());
	}
}
