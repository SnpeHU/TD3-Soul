#pragma once
#include "Bullet.h"

class Beam : public Bullet
{
public:
	Beam(Vector3 _endPos,Vector3 _startPos);
	~Beam() = default;
	void Update() override;
	void Draw(const Camera& camera) override;
private:
	Vector3 startPos;


};
