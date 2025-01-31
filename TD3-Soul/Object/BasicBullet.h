#pragma once
#include "Bullet.h"

class BasicBullet : public Bullet
{
public:
	BasicBullet(Vector3 pos, Vector3 toward, float speed);
	~BasicBullet() = default;
	void Update() override;
	void Draw(const Camera& camera) override;
};
