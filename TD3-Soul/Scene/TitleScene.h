#pragma once
#include "Scene.h"
class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene() = default;

	void onEnter() override;
	void onInput(char* keys, char* prekeys) override;
	void Update() override;
	void Draw(const Camera& camera) override;
	void onExit() override;

private:

};

