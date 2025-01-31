#pragma once
#include "Object.h"
class Wall : public Object
{
public:
	Wall(Vector3 pos,Vector3 size);
	Wall() = default;
	virtual ~Wall() = default;
	void Update() override;
	void Draw(const Camera& camera) override;
protected:
	float height;

	int topColor;
};
