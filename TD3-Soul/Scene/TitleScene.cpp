#include "TitleScene.h"
#include "Novice.h"
#include <Manager/SceneManager.h>

TitleScene::TitleScene()
{
	s_name = "Title";
}

void TitleScene::onEnter()
{
}

void TitleScene::onInput(char* keys, char* prekeys)
{
	if (keys[DIK_BACKSPACE] && !prekeys[DIK_BACKSPACE])
	{
		SceneManager::Instance()->switchScene(SceneManager::SceneType::Game);
	}
}

void TitleScene::Update()
{
}

void TitleScene::Draw(const Camera& camera)
{
	(void)camera;
}

void TitleScene::onExit()
{
}
