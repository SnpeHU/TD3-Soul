#pragma once
#include "Tool/timer.h"
#include "Charactor.h"
//#include "BulletAround.h"
#include <memory>
class PlayerBullet;
class Player : public Charactor
{
	public:
		Player() = default;
		Player(Vector3 pos);
		~Player();

		void Input(char* keys, char* prekeys) override;
		void Update() override;
		void Draw(const Camera& camera) override;

		void ClearNodes() override;

private:


	bool isUp = false;
	bool isDown = false;
	bool isLeft = false;
	bool isRight = false;

	bool isJumpButton = false;

	//翻滚控制
	bool isRollButton = false;
	bool isRolling = false;
	Timer rollTimer;
	float rolltime = 0.1f;

	//瞄准控制
	bool isAimButton = false;
	bool isAiming = false;
	bool isHaveBullet = true;
	
	float jumpForce = 10.0f;
	int curcolor;//当前颜色
	int bodycolor = 0x00FFFFFF;

	//std::vector<std::unique_ptr<BulletAround>> bullets;
	PlayerBullet* playerBullet = nullptr;


	
	int maxHp = 5;
	int hp;
	//无敌时间
	Timer invincibleTimer;
	float invincibleTime = 0.5f;
	int invincibleColor = 0x8B3A3AFF;
	bool isInvincible = false;

	

};