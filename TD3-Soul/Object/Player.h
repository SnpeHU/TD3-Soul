#pragma once
#include "Charactor.h"
//#include "BulletAround.h"
#include <memory>
class Player : public Charactor
{
	public:
		Player();
		Player(Vector3 pos);
		~Player() = default;

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

	
	float jumpForce = 10.0f;
	int bodycolor = 0x00FFFFFF;

	//角色周围飘着的子弹效果
	//std::vector<std::shared_ptr<BulletAround>> bullets;
	//子弹围绕角色的半径
	float bulletRadius = 20.0f;
	//子弹围绕角色的高度
	float bulletHeight = 10.0f;
};