#include "Object.h"
#include "Novice.h"
#include "Camera.h"
void Object::Draw(const Camera& camera)
{
	(void)camera;
	Vector2 screenPos = Transform(Vector2(0,0), objectMatrix);
	if (isDeBug)
	{
		Novice::DrawEllipse(int(screenPos.x), int(screenPos.y), 1, 1, 0.0f, 0xFF0000FF, kFillModeSolid);
	}
}
