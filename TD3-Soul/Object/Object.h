#pragma once
#include "Tool/MyVector2.h"
#include "Tool/MyVector3.h"
#include "Tool/Matrix.h"
#include "Camera.h"
#include <string>
#include "Manager/collision_box.h"
#include "Manager/collision_manager.h"
using std::string;
class Object
{
public:
	Object() = default;
	virtual ~Object();
	virtual void Update() = 0;
	virtual void Draw(const Camera& camera);

	void DrawDebug(const Camera& camera);


	Vector3 GetPos() const { return pos; };
	void SetPos(Vector3 _pos) { pos = _pos; };

	bool GetCanRemove() const { return isCanRemove; };
	void SetCanRemove(bool _isCanRemove) { isCanRemove = _isCanRemove; };

	Vector2 get_logic_center2D() const
	{
		return Vector2(pos.x, pos.y + hurtBoxSize.y / 2);
	}

	Vector3 get_logic_center() const
	{
		return Vector3(pos.x, pos.y + hurtBoxSize.y / 2,pos.z);
	}

	//gethurtbox
	CollisionBox* getHurtBox() { return hurt_box; };

	
public:
	string name = "none";

protected:

	Vector3 pos;
	Vector2 size;
	Matrix3x3 objectMatrix = {};

	CollisionBox* hurt_box = nullptr;
	Vector2 hurtBoxSize;


	bool isCanRemove = false;
	bool isDeBug = true;
	bool isShadow = true;


	int color = 0x00FFFFFF;

	Vector2 shadowSize = { 0.0f,0.0f };
	//影子颜色为黑色
	int shadowColor = 0x00000030;

};