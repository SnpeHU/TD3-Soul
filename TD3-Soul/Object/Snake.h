#pragma once
#include "Charactor.h"
#include <vector>
#include "Chain.h"

class Snake : public Charactor
{

public:
	Snake() = default;
	Snake(Vector3 pos);
	~Snake();

	virtual void Input(char* keys, char* prekeys) override;
	void Update() override;
	void Draw(const Camera& camera) override;

	void ClearNodes() override;

	void SetAngleConstraint(float azimuthalConstraint, float polarConstraint);

private:

	//链条
	Chain spine;


	//节点描画
	int nodeNum = 20;
	//节点间隔
	float nodeInterval = 20.0f;
	//Vector2 headPos;//头部位置（相对于pos）暂时无用

	//测试用
	bool isForward = false;
	bool isBack = false;
	bool isLeft = false;
	bool isRight = false;
	bool isUp = false;
	bool isDown = false;

	//bool isJumpButton = false;
	float jumpForce = 10.0f;
	//float gravity = 0.8f;



};