#pragma once
#include "Bullet.h"
//#include "Object/Charactor.h"
class BlockEmitter;
class Charactor;
class Beam : public Bullet
{
public:
	Beam(Vector3 _endPos,Vector3 _startPos,Charactor* target);
	~Beam() = default;
	void Update() override;
	void Draw(const Camera& camera) override;

	void SetStartPos(Vector3 _startPos) { startPos = _startPos; };
private:
	Vector3 startPos;
	float maxSpeed;
	float curLength = 0.0f;
	float length;//ビームの長さ

	Charactor* target = nullptr;
	Timer toGroundTimer;//
	bool isToGround = false;



	int nodeCount;
	float linkSize = 30.0f;
	Vector2 parSize = { 20.0f,20.0f };
	std::vector<Vector3> points;
	Timer emitTimer;
	float emitInterval = 0.03f;

	int emitIndex = 0;
	int emitCount = 2;

	std::unique_ptr<BlockEmitter> blockEmitter = nullptr;
};
