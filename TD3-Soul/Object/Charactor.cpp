#include "Charactor.h"
#include "Novice.h"
#include "Camera.h"
Charactor::Charactor()
{
	pos = { 0.0f,0.0f };
	toward = {1.0f,0.0f};
	size = { 20.0f,20.0f };

	leftTop = { -size.x / 2,size.y };


	isDeBug = true;

}
void Charactor::Update()
{
}
void Charactor::Draw(const Camera& camera)
{
	objectMatrix = camera.GetObjectMatrix(pos, 0.0f);
	//Vector2 vertex[4] = { {-size.x/2,size.y/2},{size.x/2,size.y/2},{-size.x/2,-size.y/2},{size.x/2,-size.y/2} };

	//for (int i = 0; i < 4; i++)
	//{
	//	vertex[i] = Transform(vertex[i], charactorMatrix);
	//}

	//Novice::DrawQuad(
	//	(int)vertex[0].x, (int)vertex[0].y,
	//	(int)vertex[1].x, (int)vertex[1].y,
	//	(int)vertex[2].x, (int)vertex[2].y,
	//	(int)vertex[3].x, (int)vertex[3].y,
	//	0, 0, 1, 1,
	//	0, WHITE);
	


	Vector2 screenleftTop = Transform(leftTop, objectMatrix);
	Novice::DrawBox(int(screenleftTop.x), int(screenleftTop.y), int(size.x), int(size.y), 0.0f, WHITE, kFillModeSolid);

	//屏幕坐标
	//Novice::DrawBox(int(pos.x - size.x / 2), int(pos.y - size.y), int(size.x), int(size.y), 0.0f, WHITE, kFillModeSolid);

	Object::Draw(camera);
	
}
