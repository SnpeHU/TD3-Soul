#pragma once
#include "Scene.h"
#include "Novice.h"
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
	int Img = Novice::LoadTexture("./rs/start.png");
	int TitleImg = Novice::LoadTexture("./rs/title.png");
	int startSprite = Novice::LoadTexture("./rs/startSprite_11.png");
	
};

