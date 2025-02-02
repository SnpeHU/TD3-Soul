#pragma once
#include "Tool/MyVector3.h"
#include "Tool/MyVector2.h"
#include "Tool/Matrix.h"
#include "Tool/timer.h"
#include "Object/Object.h"
#include "Camera.h"
#define deltaTime (1.0f/60.0f)
#define PI 3.1415926f

class Particle : public Object
{
public:
	Particle() = default;
	virtual ~Particle() = default;
	virtual void Update() override = 0 ;
	virtual void Draw(const Camera& camera) override = 0;

	int GetColor(unsigned int red, unsigned int green, unsigned int blue, int _alpha)
	{
		return color = (red << 24) | (green << 16) | (blue << 8) | _alpha;
	}

	bool GetCanRemove() const { return isCanRemove; };
protected:

	Vector3 toward;
	Vector3 velocity;
	Vector3 acceleration;


	float speed;
	float sizeSpeed;

	float lifeTime = 0.5f;
	Timer lifeTimer;


};