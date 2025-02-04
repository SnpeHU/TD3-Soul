#pragma once
#include "Charactor.h"
#include <vector>
#include "Chain.h"

class Snake : public Charactor
{

public:
	enum class SnakeBehavior
	{
		OnInput,
		Smove,
		Normol,
	};

	Snake() = default;
	Snake(Vector3 pos);
	~Snake() override;

	virtual void Input(char* keys, char* prekeys) override;
	void Update() override;
	void Draw(const Camera& camera) override;

	void SwitchBehavior(SnakeBehavior behavior);

	void Reset(Vector3 pos) override;

	void SetNodeEnableGravity(bool flag);
	void SetNodeColor(int color);
	void ClearNodes() override;

	void SetAngleConstraint(float azimuthalConstraint, float polarConstraint);

	void SetIsActive(bool flag) { isActive = flag; };

	void SetIsInvincible(bool flag) { isInvincible = flag; };
	bool GetIsInvincible() const { return isInvincible; };

	void SetPhases(int _phases) { phases = _phases; };
	int GetPhases() const { return phases; };

	int aliveNodeNum;
	int phases = 0;//階段

private:

	//链条
	Chain spine;

	SnakeBehavior curBehavior = SnakeBehavior::Normol;

	//节点描画
	int nodeNum;
	
	//节点间隔
	float nodeInterval = 20.0f;

	//测试用
	bool isForward = false;
	bool isBack = false;
	bool isLeft = false;
	bool isRight = false;
	bool isUp = false;
	bool isDown = false;

	//bool isJumpButton = false;
	float jumpForce = 10.0f;

	//蛇行移动
	float sMoveTime = 0.0f;
	float moveRange = 4.0f;

	bool isActive = true;

	Timer invincibleTimer;
	float invincibleTime = 0.3f;
	bool isInvincible = false;

	

};