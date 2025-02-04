#pragma once
#include "Tool/timer.h"
#include "Tool/MyVector2.h"
#include "Tool/Matrix.h"
#include "Novice.h"

#define deltaTime (1.0f/60.0f)
extern float windowHeight;
extern float windowWidth;
class Object;
class Camera
{
public:
	Camera(Vector2 _pos);
	~Camera() = default;


	void Reset();


	void Input(char* keys);
	

	void Update();


	void Shake(float power, float time);


	Matrix3x3 GetViewMatrix() const;


	Matrix3x3 GetCameraMatrix() const;


	Matrix3x3 GetObjectMatrix(const Vector2& worldPos, float objectRotation) const;

	Vector2 ScreenToWorld(const Vector2& screenPos) const;

	void SetTarget(Object* _target);


	const Vector2& GetPos() const
	{
		return pos;
	}

	void SetPos(const Vector2& _pos)
	{
		pos = _pos;
	}

	void SetSize(const Vector2& _size)
	{
		size = _size;
	}

	void SetRotation(float _rotation)
	{
		rotation = _rotation;
	}

	float GetScale() const
	{
		return scale;
	}

	void SetScale(float _scale)
	{
		scale = _scale;
	}
private:
	Vector2 pos;
	Vector2 originalPos; // 用于存储摄像机抖动前位置
	Vector2 size;
	float rotation;
	float scale;
	float angle;//摄像机角度

	Matrix3x3 view = {};
	Matrix3x3 projection = {};
	Matrix3x3 viewport = {};


	float speed = 3.0f;
	

	//摄像机抖动
	Timer shakeTimer;
	float shakePower = 0;
	bool isShake = false;
	Vector2 shakePos = { 0,0 };

	Object* target = nullptr;
	public:
		float heightscale = 0.5f;//角色高度投影到地面的比例
};
