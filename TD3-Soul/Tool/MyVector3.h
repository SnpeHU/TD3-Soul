#pragma once
#ifndef _VECTOR3_H_
#define _VECTOR3_H_
#include <vector>
#include <cmath>
class Vector3
{
public:
    float x = 0;
    float y = 0;
    float z = 0;

public:
    Vector3() = default;
    ~Vector3() = default;

    Vector3(float x, float y, float z)
        : x(x), y(y), z(z) {
    }

	//间隔插值
    static Vector3 lerp(const Vector3& start, const Vector3& end, float t) {
        return Vector3(
            start.x + t * (end.x - start.x),
            start.y + t * (end.y - start.y),
            start.z + t * (end.z - start.z)
        );
    }

    Vector3 operator+(const Vector3& vec) const
    {
        return Vector3(x + vec.x, y + vec.y, z + vec.z);
    }

    void operator+=(const Vector3& vec)
    {
        x += vec.x, y += vec.y, z += vec.z;
    }

    void operator-=(const Vector3& vec)
    {
        x -= vec.x, y -= vec.y, z -= vec.z;
    }

    Vector3 operator-(const Vector3& vec) const
    {
        return Vector3(x - vec.x, y - vec.y, z - vec.z);
    }

    float operator*(const Vector3& vec) const
    {
        return x * vec.x + y * vec.y + z * vec.z;
    }

    Vector3 operator*(float val) const
    {
        return Vector3(x * val, y * val, z * val);
    }

    void operator*=(float val)
    {
        x *= val, y *= val, z *= val;
    }

    float length() const
    {
        return sqrt(x * x + y * y + z * z);
    }

    Vector3 normalize() const
    {
        float len = length();

        if (len == 0)
            return Vector3(0, 0, 0);

        return Vector3(x / len, y / len, z / len);
    }

    Vector3 copy() const {
        return Vector3(x, y, z);
    }

    static Vector3 add(const Vector3& a, const Vector3& b) {
        return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    static Vector3 sub(const Vector3& a, const Vector3& b) {
        return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    std::pair<float, float> heading() const {
        float r = sqrt(x * x + y * y + z * z);
        float theta = acos(z / r); // 极角
        float phi = atan2(y, x); // 方位角
        return std::make_pair(phi, theta);
    }

	// 设置向量的大小
    Vector3 setMag(float mag) {
        float currentMag = sqrt(x * x + y * y + z * z);
        if (currentMag != 0) {
            x = (x / currentMag) * mag;
            y = (y / currentMag) * mag;
            z = (z / currentMag) * mag;
        }
        return *this;
    }




    static Vector3 fromAngle(float theta, float phi) {
        return Vector3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta)); // 适用于三维空间
    }
};
#endif // !_VECTOR3_H_