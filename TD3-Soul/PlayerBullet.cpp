#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(Vector3 pos)
{
	this->pos = pos;
	//toward = { 1.0f,0.0f,0.0f };
	size = { 10.0f,10.0f };
	speed = 10.0f;
	color = 0x00FFFFFF;
}
