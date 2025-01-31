#pragma once
#include "Particle.h"
class CircleParticle : public Particle
{
public:
	CircleParticle(Vector3 pos ,float lifeTime,float speed);
	CircleParticle() = default;
	~CircleParticle() = default;
	void Update() override;
	void Draw(const Camera& camera) override;
private:
};