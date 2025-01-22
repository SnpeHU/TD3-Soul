#include "TestScene.h"
#include <Manager/SceneManager.h>

#ifdef _DEBUG
#include <imgui.h>
#endif // DEBUG

TestScene::TestScene()
{
	s_name = "Test";
}

void TestScene::onEnter()
{
	snake = new Snake_D(Vector2(400, 300));
}

void TestScene::onInput(char* keys, char* prekeys)
{
	(void)keys;
	(void)prekeys;
	if (keys[DIK_G] && !prekeys[DIK_G])
	{
		SceneManager::Instance()->switchScene(SceneManager::SceneType::Game);
	}
	snake->Input(keys, prekeys);
}

void TestScene::Update()
{
	int x, y;
	Novice::GetMousePosition(&x, &y);
	snake->resolve();
	//snake->resolve();
}

void TestScene::Draw(const Camera& camera)
{
	(void)camera;
	snake->display();

#ifdef _DEBUG
	ImGui::Begin("Snake_D");
	//ImGui::DragFloat("x", &snake->pos.x, 1.0f, 0.0f, 800.0f);
	ImGui::End();

#endif
}

void TestScene::onExit()
{
}

