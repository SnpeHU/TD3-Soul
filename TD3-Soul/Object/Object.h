#pragma once
#include "Tool/MyVector2.h"
#include "Tool/Matrix.h"
class Camera;
class Object
{
public:
	Object() = default;
	virtual ~Object() = default;
	virtual void Update() = 0;
	virtual void Draw(const Camera& camera);


	Vector2 GetPos() { return pos; };
	void SetPos(Vector2 _pos) { pos = _pos; };


protected:

	Vector2 pos;
	Matrix3x3 objectMatrix = {};
	bool isDeBug = false;

};