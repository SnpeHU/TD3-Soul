#pragma once
#include "Wall.h"
class ButtonWall : public Wall
{
public:
	ButtonWall(Vector3 pos, Vector3 size);
	~ButtonWall() = default;
	void Update() override;
	void Draw(const Camera& camera) override;


	void SetOnTrigger(std::function<void()> _onTrigger);

private:
	std::function<void()> onTrigger;
};
