#include "Camera.h"
#include "Object/Object.h"
Camera::Camera(Vector2 _pos)
{
	
	pos = _pos;
	originalPos = _pos;
	size = Vector2(windowWidth, windowHeight);
	rotation = 0.0f;
	scale = 1.0f;
	angle = 0.0f;



	//设置摄像机抖动
	shakeTimer.set_one_shot(true);
	shakeTimer.set_on_timeout([&]() {
		isShake = false;
		shakePos = { 0,0 };
		pos = originalPos;
		});

	//添加摄像机倾斜角度（透视投影）（有问题）
		//return MakeObliqueOrthographicMatrix(-size.x / 2, size.y / 2, size.x / 2, -size.y / 2, angle);
	projection = MakeOrthographicMatrix(-size.x / 2, size.y / 2, size.x / 2, -size.y / 2);
	viewport = MakeViewportMartrix(0, 0, windowWidth, windowHeight);
	
}

void Camera::Reset()
{
	pos = Vector2(0, 0);
	originalPos = pos;
	rotation = 0.0f;
	scale = 1.0f;
	angle = 0.0f;
	isShake = false;
	target = nullptr;
}

void Camera::Input(char* keys)
{
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
			pos.x -= speed;
		}
		if (keys[DIK_RIGHT])
		{
			pos.x += speed;
		}

		//if (keys[DIK_Z])
		//{
		//	scale += 0.05f;
		//}
		//if (keys[DIK_X])
		//{
		//	scale -= 0.05f;
		//}
		//if (keys[DIK_C])
		//{
		//	angle += 0.05f;
		//}
		//if (keys[DIK_V])
		//{
		//	angle -= 0.05f;
		//}
	}
}

void Camera::Update()
{
	//cameraMatrix = GetCameraMatrix(size.x, size.y);
	view = GetViewMatrix();
	shakeTimer.on_update(deltaTime);
	if (isShake)
	{
		shakePos.x = (-50 + rand() % 100) / 50.0f * shakePower;
		shakePos.y = (-50 + rand() % 100) / 50.0f * shakePower;
		pos = originalPos + shakePos;
	}

	if (target)
	{
		//缓动跟随目标,距离越远速度越快
		Vector2 dir;
		dir.x = target->GetPos().x - pos.x;
		dir.y = target->GetPos().y - pos.y;
		float dis = dir.length();
		if (dis > 5.0f)
		{
			pos.x += dir.x * 0.1f;
			pos.y += dir.y * 0.1f;
			originalPos = pos;
		}
	}
}

void Camera::Shake(float power, float time)
{
	shakePower = power;
	shakeTimer.set_wait_time(time);
	shakeTimer.restart();
	isShake = true;
}

Matrix3x3 Camera::GetViewMatrix() const
{
	Matrix3x3 translate = MakeTranslateMatrix(pos);
	Matrix3x3 rotate = MakeRotateMatrix(-rotation);
	Matrix3x3 scale_matrix = MakeScaleMatrix(scale);
	Matrix3x3 worldCameraMatrix = Multiply(Multiply(rotate, scale_matrix), translate);
	return Inverse(worldCameraMatrix);

	//return Multiply(rotate, translate);
}

Matrix3x3 Camera::GetCameraMatrix() const
{
	return Multiply(Multiply(view, projection), viewport);
}

Matrix3x3 Camera::GetObjectMatrix(const Vector2& worldPos, float objectRotation) const
{
	Matrix3x3 translate = MakeTranslateMatrix(worldPos);
	Matrix3x3 rotate = MakeRotateMatrix(objectRotation);
	Matrix3x3 objectMatrix = Multiply(rotate, translate);
	objectMatrix = Multiply(objectMatrix, view);
	objectMatrix = Multiply(objectMatrix, projection);
	objectMatrix = Multiply(objectMatrix, viewport);
	return objectMatrix;
}

void Camera::SetTarget(Object* _target)
{
	target = _target;
}
