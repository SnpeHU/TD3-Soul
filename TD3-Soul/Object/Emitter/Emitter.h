#pragma once
#include "Object/Object.h"
#include "vector"
class Particle;
class Emitter : public Object
{
public:
	Emitter() = default;
	virtual ~Emitter();
	virtual void Update() override;
	virtual void Draw(const Camera& camera) override = 0;

	void SetEnable(bool flag) { isEnable = flag; };
	bool GetEnable() const { return isEnable; };

	void SetEmitInterval(float interval) { emitInterval = interval; };

protected:
	std::vector<Particle*> particles;

	bool isEnable = true;

	Timer emitTimer;
	float emitInterval = 0.01f;

};