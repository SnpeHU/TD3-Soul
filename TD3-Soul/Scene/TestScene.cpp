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
	frontColor = 0x00000000;
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
	//如果正在切换场景，前景色逐渐变黑
	if (SceneManager::Instance()->getIsSwitchingScene())
	{

		//frontColor
		float t = SceneManager::Instance()->getSwitchSceneTimer().get_progress();
		if (t >= 1.0f)
		{
			t = 1.0f;

		}
		frontColor = Vector2().GetColor(0, 0, 0, int(255 * t));
		//SceneManager::Instance()->getSwitchSceneTimer().get_progress();
		//frontColor 的透明度随着时间逐渐变低

	}
}

void TestScene::Draw(const Camera& camera)
{
	(void)camera;
	Novice::DrawBox(0, 0, (int)windowWidth, (int)windowHeight, 0.0f, backColor, kFillModeSolid);
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

