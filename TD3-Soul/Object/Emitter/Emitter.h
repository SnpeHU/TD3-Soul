#pragma once
#include "Object/Object.h"
#include "Manager/ObjectManager.h"
#include "vector"
class Particle;
class Emitter : public Object
{
public:
	Emitter() = default;
	virtual ~Emitter() = default;
	virtual void Update() override;
	virtual void Draw(const Camera& camera) override = 0;

	void SetEnable(bool flag) { isEnable = flag; };
	bool GetEnable() const { return isEnable; };

	void SetEmitInterval(float interval) { emitInterval = interval; };

protected:
	//std::vector<Particle*> particles;

	bool isEnable = false;

	Timer emitTimer;
	float emitInterval = 0.01f;

	Vector2 particleSize = {5.0f,5.0f};
	Vector3 particleToward = { 0.0f,0.0f,0.0f };
	Vector3 particleAcceleration = { 0.0f,0.0f,0.0f };
	float particleSpeed = 2.0f;
	float particleLifeTime = 1.0f;
	int particleColor = 0xFFFFFFFF;
	


};