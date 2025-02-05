#include "TitleScene.h"
#include "Novice.h"
#include <Manager/SceneManager.h>
#include "Manager/ObjectManager.h"
#include "Manager/CharactorManager.h"
#include "Manager/collision_manager.h"
#include "Object/Wall.h"
#include "Object/ButtonWall.h"
#include "Camera.h"
extern Camera m_camera;

TitleScene::TitleScene()
{
	s_name = "Title";
}

void TitleScene::onEnter()
{
	m_camera.Reset();
	m_camera.SetPos(Vector2(0.0f, 0.0f));
	CharactorManager::Instance()->RespwanPlayer(Vector3(0.0f, 0.0f, 0.0f));
	frontColor = 0x00000000;

	auto wall = std::make_unique<Wall>(Vector3(-690.0f, -800.0f, 0.0f), Vector3(350.0f, 1100.0f, 200.0f));//出生点左的墙
	auto wall2 = std::make_unique<Wall>(Vector3(690.0f, -800.0f, 0.0f), Vector3(350.0f, 1100.0f, 200.0f));//出生点右的墙
	auto wall3 = std::make_unique<Wall>(Vector3(0.0f, 250.0f, 0.0f), Vector3(2000.0f, 600.0f, 100.0f));//出生点后的墙
	auto wall4 = std::make_unique<Wall>(Vector3(0.0f, -950.0f, 0.0f), Vector3(2000.0f, 600.0f, 100.0f));//出生点后的墙
	ObjectManager::Instance()->AddObject(std::move(wall));
	ObjectManager::Instance()->AddObject(std::move(wall2));
	ObjectManager::Instance()->AddObject(std::move(wall3));
	ObjectManager::Instance()->AddObject(std::move(wall4));

	auto buttonWallnext = std::make_unique<ButtonWall>(Vector3(-150.0f, 0.0f, 0.0f), Vector3(80.0f, 80.0f, 60.0f));
	buttonWallnext->SetOnTrigger([this]() {
		SceneManager::Instance()->DelayedSwitchScene(SceneManager::SceneType::Game, 1.0f);//1秒後にシーンを切り替える
		m_camera.Shake(1.0f, 10.0f);
		});
	buttonWallnext->SetImg(TitleImg);

	ObjectManager::Instance()->AddObject(std::move(buttonWallnext));

	auto buttonWallnext2 = std::make_unique<ButtonWall>(Vector3(150.0f, 0.0f, 0.0f), Vector3(80.0f, 80.0f, 60.0f));
	buttonWallnext2->SetOnTrigger([this]() {
		SceneManager::Instance()->DelayedSwitchScene(SceneManager::SceneType::Game, 1.0f);
		m_camera.Shake(1.0f, 10.0f);
		});
	buttonWallnext2->SetImg(startSprite);
	buttonWallnext2->isRotate = true;
	ObjectManager::Instance()->AddObject(std::move(buttonWallnext2));


	auto titleWall = std::make_unique<Wall>(Vector3(0.0f, -200.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));//出生点后的墙
}

void TitleScene::onInput(char* keys, char* prekeys)
{

	if (keys[DIK_BACKSPACE] && !prekeys[DIK_BACKSPACE])
	{
		//SceneManager::Instance()->switchScene(SceneManager::SceneType::Game);
	}
	CharactorManager::Instance()->onInput(keys, prekeys);
}

void TitleScene::Update()
{
	m_camera.Update();
	CollisionManager::Instance()->ProcessCollision();
	ObjectManager::Instance()->Update();

	//如果正在切换场景，前景色逐渐变黑
	if (SceneManager::Instance()->getIsSwitchingScene())
	{

		//frontColor
		float t = SceneManager::Instance()->getSwitchSceneTimer().get_progress();
		if (t>=1.0f)
		{
			t = 1.0f;

		}
        frontColor = Vector2().GetColor(0, 0, 0, int(255 * t));

	}


}

void TitleScene::Draw(const Camera& camera)
{
	Novice::DrawBox(0, 0, (int)windowWidth, (int)windowHeight, 0.0f, backColor, kFillModeSolid);
	ObjectManager::Instance()->Draw(camera);
#ifdef _DEBUG
	CollisionManager::Instance()->onDebugRender(camera);
#endif // DEBUG
	Novice::DrawBox(0, 0, (int)windowWidth, (int)windowHeight, 0.0f, frontColor, kFillModeSolid);
}

void TitleScene::onExit()
{
	m_camera.Reset();
	CharactorManager::Instance()->RemoveAllCharactors();
	ObjectManager::Instance()->RemoveAllObject();


}
