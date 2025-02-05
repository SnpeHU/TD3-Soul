#pragma once
#include "Wall.h"
#include "Novice.h"
class ButtonWall : public Wall
{
public:
	ButtonWall(Vector3 pos, Vector3 size);
	~ButtonWall() = default;
	void Update() override;
	void Draw(const Camera& camera) override;

	
	uint32_t LerpColor(uint32_t startColor, uint32_t endColor, float t);

	void SetImg(int _img) { img = _img; };
	void SetOnTrigger(std::function<void()> _onTrigger);

	bool isRotate = false;

private:
	std::function<void()> onTrigger;

	Timer tirggerTimer;
	float triggerTime = 1.0f;

	Timer colorChangeTimer;
	float colorChangeTime = 1.0f;

	int tipColor = 0xe57e7eFF;
	int originTopColor;

	Vector2 imgPos;
	int img = 0;

	

	float MoveTime = 0.0f;
	float moveRange = 6.0f;
	float offset = 0.0f;

	int stoneAudio = Novice::LoadAudio("./rs/stone.wav");

	float rotateSpeed = 0.03f;
	float rotate = 0.0f;
	Vector2 corners[4];
	Vector3 rotateCenter;
	
};
