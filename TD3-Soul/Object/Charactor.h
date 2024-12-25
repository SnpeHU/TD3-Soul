#pragma once
#include "Object.h"
#include "Tool/Matrix.h"
class Charactor : public Object
{
public:
	Charactor();
	~Charactor() = default;

	//virtual void Input(char* keys, char* prekeys) = 0;
	virtual void Update() override;
	virtual void Draw(const Camera& camera) override;

private:
	//位置取角色底部中心
	Vector2 size;
	Vector2 toward;

	//默认为DrawBox的左上角
	Vector2 leftTop;
	


	bool isDead = false;

};
