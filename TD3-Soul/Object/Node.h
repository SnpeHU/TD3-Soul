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

	void setCanHurt(bool flag) { isCanHurt = flag; };
	bool getCanHurt() const { return isCanHurt; };

	void setisDestroyed(bool flag) { isDestroyed = flag; };
	bool getisDestroyed() const { return isDestroyed; };

private:
	
	//Vector2 size;
	Vector2 drawPos;

	int bordercolor;
	int boderwidth;

	bool isCanHurt = false;
	bool isDestroyed = false;

};
