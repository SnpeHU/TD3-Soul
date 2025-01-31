#pragma once
#include "Tool/MyVector3.h"
#include "Tool/MyVector2.h"
#include "Tool/Matrix.h"
#include "Tool/timer.h"
#include "Camera.h"
#define deltaTime (1.0f/60.0f)
#define PI 3.1415926f

class Particle
{
public:
	Particle() = default;
	virtual ~Particle() = default;
	virtual void Update() = 0;
	virtual void Draw(const Camera& camera) = 0;

	int GetColor(unsigned int red, unsigned int green, unsigned int blue, int _alpha)
	{
		return color = (red << 24) | (green << 16) | (blue << 8) | _alpha;
	}

	bool GetCanRemove() const { return isCanRemove; };
protected:
	Vector3 pos;
	Vector3 toward;
	Vector3 velocity;
	Vector3 acceleration;

	Matrix3x3 objectMatrix = {};

	Vector2 size;
	float speed;

	float lifeTime;
	Timer lifeTimer;
	int color;

	bool isCanRemove = false;

};