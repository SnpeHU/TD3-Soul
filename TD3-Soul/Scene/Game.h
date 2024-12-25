#pragma once
#include "Scene.h"
class Game : public Scene
{
public:
	//赋值场景名字
	Game();
	~Game() = default;

	void onEnter() override;
	void onInput(char* keys, char* prekeys) override;
	void Update() override;
	void Draw(const Camera& camera) override;
	void onExit() override;

private:

};
