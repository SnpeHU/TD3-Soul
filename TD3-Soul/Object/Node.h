#pragma once
#include <Object/Charactor.h>
#include <Tool/MyVector3.h>
class Node : public Charactor
{
public:
	Node(Vector3 pos);
	~Node() = default;

	void Update() override;
	void Draw(const Camera& camera) override;

private:
	
	//Vector2 size;
	Vector2 drawPos;

	int bordercolor;
	int boderwidth;

};
