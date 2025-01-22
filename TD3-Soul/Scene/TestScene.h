#pragma once
#include "Scene.h"
#include "Object/Snake_D.h"
class TestScene : public Scene
{
public:
	TestScene();
	~TestScene() = default;
	void onEnter() override;
	void onInput(char* keys, char* prekeys) override;
	void Update() override;
	void Draw(const Camera& camera) override;
	void onExit() override;
private:
	Snake_D* snake = nullptr;

};