#pragma once
#include "Emitter.h"
class CircleEmitter : public Emitter
{
public:
	CircleEmitter(Vector3 pos, float emitInterval);
	~CircleEmitter() = default;
	void Update() override;
	void Draw(const Camera& camera) override;
private:
};