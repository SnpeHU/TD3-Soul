#pragma once
#include "Emitter.h"
class BlockEmitter : public Emitter
{
public:
	BlockEmitter(Vector3 pos, float emitInterval);//用于射线集中地面粒子
	BlockEmitter(Vector3 pos, float emitInterval, Vector2 particleSize, Vector3 particleToward, Vector3 particleAcceleration, float particleLifeTime, float particleSpeed, int particleColor);
	~BlockEmitter() = default;
	void Update() override;
	void Draw(const Camera& camera) override;

private:
};