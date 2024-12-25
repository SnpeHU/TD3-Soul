#pragma once
#include "Tool/timer.h"
#include "Tool/MyVector2.h"
#include "Tool/Matrix.h"

extern float windowHeight;
extern float windowWidth;



class Camera
{
public:
	Camera(Vector2 _pos)
	{
		pos = _pos;
		size = Vector2(windowWidth,windowHeight);
		rotation = 0.0f;



		//设置摄像机抖动
		shakeTimer.set_one_shot(true);
		shakeTimer.set_on_timeout([&]() {
			isShake = false; 
			shakePos = { 0,0 };
			});
	};
	~Camera() = default;

	void Reset()
	{
		pos = Vector2(0, 0);
		rotation = 0.0f;
	}

	void Input(char* keys)
	{
		if (keys[DIK_UP])
		{
			pos.y += speed;
		}
		if (keys[DIK_DOWN])
		{
			pos.y -= speed;
		}
		if (keys[DIK_LEFT])
		{
			pos.x += speed;
		}
		if (keys[DIK_RIGHT])
		{
			pos.x -= speed;
		}

		if (keys[DIK_Z])
		{
			rotation += 0.1f;
		}
		if (keys[DIK_X])
		{
			rotation -= 0.1f;
		}
	}

	void Update()
	{
		//cameraMatrix = GetCameraMatrix(size.x, size.y);
		view = GetViewMatrix();
		projection = GetProjectionMatrix();
		viewport = GetViewportMatrix(size.x, size.y);


		shakeTimer.on_update(deltaTime);
		if (isShake)
		{
			shakePos.x = (-50 + rand() % 100) / 50.0f * shakePower;
			shakePos.y = (-50 + rand() % 100) / 50.0f * shakePower;
			pos.x += shakePos.x;
			pos.y += shakePos.y;
		}
	}

	void Shake(float power, float time)
	{
		shakePower = power;
		shakeTimer.set_wait_time(time);
		shakeTimer.restart();
		isShake = true;
	}

	Matrix3x3 GetViewMatrix() const
	{
		Matrix3x3 translate = MakeTranslateMatrix(Vector2(-pos.x, pos.y));
		Matrix3x3 rotate = MakeRotateMatrix(-rotation);
		Matrix3x3 worldCameraMatrix = Multiply(rotate , translate);
		return Inverse(worldCameraMatrix);

		//return Multiply(rotate, translate);
	}

	Matrix3x3 GetProjectionMatrix() const
	{
		return MakeOrthographicMatrix(-size.x / 2, size.y / 2, size.x / 2, -size.y / 2);
		//return MakeOrthographicMatrix(0.0f, size.y, size.x, 0.0f);
	}

	Matrix3x3 GetViewportMatrix(float _windowWidth,float _windowHeight) const
	{
		return MakeViewportMartrix(0, 0, _windowWidth, _windowHeight);
	}

	Matrix3x3 GetObjectMatrix(const Vector2& worldPos,float objectRotation) const
	{
		Matrix3x3 translate = MakeTranslateMatrix(worldPos);
		Matrix3x3 rotate = MakeRotateMatrix(objectRotation);
		Matrix3x3 objectMatrix = Multiply(translate,rotate);
		objectMatrix = Multiply(objectMatrix,view );
		objectMatrix = Multiply(objectMatrix, projection);
		objectMatrix = Multiply(objectMatrix, viewport);
		return objectMatrix;
	}

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
private:
	Vector2 pos;
	Vector2 size;
	float rotation;

	Matrix3x3 view = {};
	Matrix3x3 projection = {};
	Matrix3x3 viewport = {};


	float speed = 3.0f;


	//摄像机抖动
	Timer shakeTimer;
	float shakePower = 0;
	bool isShake = false;
	Vector2 shakePos = { 0,0 };

	float deltaTime = 1.0f / 60.0f;
};
