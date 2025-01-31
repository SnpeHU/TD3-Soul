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
	m_camera.SetPos(Vector2(0.0f, 0.0f));
	CharactorManager::Instance()->RespwanPlayer(Vector3(0.0f, 0.0f, 0.0f));

	auto wall = std::make_shared<Wall>(Vector3(-690.0f, -800.0f, 0.0f), Vector3(350.0f, 1000.0f, 200.0f));//出生点左的墙
	auto wall2 = std::make_shared<Wall>(Vector3(690.0f, -800.0f, 0.0f), Vector3(350.0f, 1000.0f, 200.0f));//出生点右的墙
	auto wall3 = std::make_shared<Wall>(Vector3(0.0f, 250.0f, 0.0f), Vector3(2000.0f, 600.0f, 100.0f));//出生点后的墙
	auto wall4 = std::make_shared<Wall>(Vector3(0.0f, -950.0f, 0.0f), Vector3(2000.0f, 600.0f, 100.0f));//出生点后的墙
	ObjectManager::Instance()->AddObject(wall);
	ObjectManager::Instance()->AddObject(wall2);
	ObjectManager::Instance()->AddObject(wall3);
	ObjectManager::Instance()->AddObject(wall4);


	auto buttonWallnext = std::make_shared<ButtonWall>(Vector3(-150.0f, 0.0f, 0.0f), Vector3(80.0f, 80.0f, 60.0f));
	buttonWallnext->SetOnTrigger([this]() {
		SceneManager::Instance()->setNextScene(SceneManager::SceneType::Game);
		

		});

	ObjectManager::Instance()->AddObject(buttonWallnext);

	auto buttonWallnext2 = std::make_shared<ButtonWall>(Vector3(150.0f, 0.0f, 0.0f), Vector3(80.0f, 80.0f, 60.0f));
	buttonWallnext2->SetOnTrigger([this]() {
		SceneManager::Instance()->setNextScene(SceneManager::SceneType::Game);

		});

	ObjectManager::Instance()->AddObject(buttonWallnext2);






}

void TitleScene::onInput(char* keys, char* prekeys)
{
	if (keys[DIK_BACKSPACE] && !prekeys[DIK_BACKSPACE])
	{
		SceneManager::Instance()->switchScene(SceneManager::SceneType::Game);
	}
	CharactorManager::Instance()->onInput(keys, prekeys);
}

void TitleScene::Update()
{
	m_camera.Update();
	CollisionManager::Instance()->ProcessCollision();
	ObjectManager::Instance()->Update();
}

void TitleScene::Draw(const Camera& camera)
{
	ObjectManager::Instance()->Draw(camera);
}

void TitleScene::onExit()
{
	m_camera.Reset();


}
