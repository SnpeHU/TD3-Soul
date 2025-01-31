#include "Object.h"
#include "Novice.h"

#include "Camera.h"



Object::~Object()
{
	if (hurt_box)
	{
		CollisionManager::Instance()->DestroyCollisionBox(hurt_box);
	}
}

void Object::Draw(const Camera& camera)
{
	//(void)camera;
	objectMatrix = camera.GetObjectMatrix(Vector2(pos.x, pos.y), 0.0f);
	Vector2 shadowPos = Transform(Vector2(0.0f, 0.0f), objectMatrix);

	Novice::DrawEllipse(int(shadowPos.x), int(shadowPos.y), int(shadowSize.x), int(shadowSize.y), 0.0f, shadowColor, kFillModeSolid);
}

void Object::DrawDebug(const Camera& camera)
{
	if (isDeBug)
	{
		// 获取摄像机矩阵
		Matrix3x3 cameraMatrix = camera.GetCameraMatrix();
		// 将对象的世界坐标转换为屏幕坐标
		Vector2 screenPos = TransformFrom3D(pos, cameraMatrix, camera.heightscale);
		Novice::DrawEllipse(int(screenPos.x), int(screenPos.y), 1, 1, 0.0f, 0xFF0000FF, kFillModeSolid);
	}
}
