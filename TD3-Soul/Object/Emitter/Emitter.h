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

	void SetParticleSize(Vector2 _size) { parSize = _size; };
	void SetParticleToward(Vector3 _toward) { parToward = _toward; };
	void SetParticleAcc(Vector3 _acc) { parAcc = _acc; };
	void SetParticleSpeed(float _speed) { parSpeed = _speed; };
	void SetParticleLifeTime(float _lifeTime) { parLifeTime = _lifeTime; };
	void SetRotateSpeed(float _speed) { rotateSpeed = _speed; };
	void SetParticleColor(int _color) { parColor = _color; };


protected:
	//std::vector<Particle*> particles;

	bool isEnable = false;

	Timer emitTimer;
	float emitInterval = 0.01f;

	Vector2 parSize = {5.0f,5.0f};
	Vector3 parToward = { 0.0f,0.0f,0.0f };
	Vector3 parAcc = { 0.0f,0.0f,0.0f };
	float parSpeed = 2.0f;
	float parLifeTime = 1.0f;
	float rotateSpeed = 0.0f;
	int parColor = 0xFFFFFFFF;
	


};