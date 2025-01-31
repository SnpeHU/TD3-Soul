#pragma once
#include "Emitter.h"
class BlockEmitter : public Emitter
{
public:
	BlockEmitter(Vector3 pos, float emitInterval);
	~BlockEmitter() = default;
	void Update() override;
	void Draw(const Camera& camera) override;

private:
};