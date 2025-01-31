#pragma once
#include "Particle.h"
class BlockParticle : public Particle
{
public:
	BlockParticle(Vector3 pos, Vector3 toward,float lifeTime);
	//BlockParticle(Vector3 pos, Vector3 toward, Vector2 size, float lifeTime);
	BlockParticle() = default;
	~BlockParticle() = default;
	void Update() override;
	void Draw(const Camera& camera) override;
private:
	Vector2 leftTop;
};