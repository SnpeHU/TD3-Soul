#pragma once
#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <cmath>
class Vector2
{
public:
	float x = 0;
	float y = 0;

public:
	Vector2() = default;
	~Vector2() = default;

	Vector2(float x, float y)
		: x(x), y(y) { }

	Vector2 operator+(const Vector2& vec) const
	{
		return Vector2(x + vec.x, y + vec.y);
	}

	void operator+=(const Vector2& vec)
	{
		x += vec.x, y += vec.y;
	}

	void operator+=(const float val)
	{
		x += val, y += val;
	}

	void operator-=(const Vector2& vec)
	{
		x -= vec.x, y -= vec.y;
	}

	Vector2 operator-(const Vector2& vec) const
	{
		return Vector2(x - vec.x, y - vec.y);
	}

	float operator*(const Vector2& vec) const
	{
		return x * vec.x + y * vec.y;
	}

	Vector2 operator*(float val) const
	{
		return Vector2(x * val, y * val);
	}

	void operator*=(float val)
	{
		x *= val, y *= val;
	}

	float length()
	{
		return sqrt(x * x + y * y);
	}

	Vector2 normalize()
	{
		float len = length();

		if (len == 0)
			return Vector2(0, 0);

		return Vector2(x / len, y / len);
	}

	
	Vector2 copy() const {
		return Vector2(x, y);
	}

	static Vector2 add(const Vector2& a, const Vector2& b) {
		return Vector2(a.x + b.x, a.y + b.y);
	}

	static Vector2 sub(const Vector2& a, const Vector2& b) {
		return Vector2(a.x - b.x, a.y - b.y);
	}

	float heading() const {
		return atan2(y, x);
	}

	Vector2 setMag(float mag) {
		float currentMag = sqrt(x * x + y * y);
		if (currentMag != 0) {
			x = (x / currentMag) * mag;
			y = (y / currentMag) * mag;
		}
		return *this;
	}

	static Vector2 fromAngle(float angle) {
		return Vector2(cos(angle), sin(angle));
	}



};


#endif // !_VECTOR2_H_
