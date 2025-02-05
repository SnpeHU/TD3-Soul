#pragma once
#include "Bullet.h"

//范围攻击子弹
class BasicBullet : public Bullet
{
public:
	BasicBullet(Vector3 pos, Vector3 target);
	BasicBullet() = default;
	~BasicBullet() = default;
	void Update() override;
	void Draw(const Camera& camera) override;
private:
	Timer moveTimer;
	float moveltime = 3.0f;
	bool isArrive = false;


	float jumpHeight = 600.0f;


	Timer lifeTimer;
	float lifeTime = 6.0f;

	Vector2 size = { 200,200 };
	Vector3 startPos;
	Vector3 targetPos;
};
