#pragma once
#include "Object/Object.h"

class Bullet : public Object
{
public:
	Bullet(Vector3 pos);
	void Update();
	void Draw(const Camera& camera);
};