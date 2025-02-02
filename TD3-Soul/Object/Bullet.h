#pragma once
#include "Object.h"
class Bullet : public Object
{
public:
	Bullet() = default;
	virtual ~Bullet() = default;

	virtual void Update() override;
	virtual void Draw(const Camera& camera) override = 0;

	void SetToward(Vector3 _toward) { toward = _toward; };
	Vector3 GetToward() const { return toward; };

	void SetSpeed(float _speed) { speed = _speed; };
	float GetSpeed() const { return speed; };

	void SetVelocity(Vector3 _velocity) { velocity = _velocity; };
	Vector3 GetVelocity() const { return velocity; };

	void SetAcceleration(Vector3 _acceleration) { acceleration = _acceleration; };
	Vector3 GetAcceleration() const { return acceleration; };




protected:
	Vector3 toward = {0.0f,0.0f,0.0f};
	Vector3 acceleration = { 0.0f,0.0f,0.0f };
	Vector3 velocity = { 0.0f,0.0f,0.0f };
	float speed;
};