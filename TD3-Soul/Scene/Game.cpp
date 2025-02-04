#include "Game.h"
#include "Manager/SceneManager.h"
#include "Manager/ObjectManager.h"
#include "Manager/CharactorManager.h"
#include "Manager/collision_manager.h"
#include "Object/Wall.h"
#include "Object/Emitter/BlockEmiiter.h"
#include "Object/Emitter/CircleEmitter.h"
#include "Novice.h"
#include "Camera.h"
extern Camera m_camera;
Game::Game()
{
	s_name = "Game";
}

void Game::onEnter()
{
	frontColor = 0x00000000;

	CharactorManager::Instance()->RespwanPlayer(Vector3(0.0f,0.0f,0.0f));
	CharactorManager::Instance()->RespwanSnake();
	
	m_camera.SetTarget(CharactorManager::Instance()->GetPlayer());
	isOver = false;

	//ロードマップ
	//auto wall = std::make_unique<Wall>(Vector3(-690.0f, -800.0f, 0.0f), Vector3(350.0f, 1000.0f, 200.0f));//出生点左的墙
	Wall* wall = new Wall(Vector3(-1040.0f, -800.0f, 0.0f), Vector3(650.0f, 2000.0f, 200.0f));//出生点左的墙
	//auto wall2 = std::make_unique<Wall>(Vector3(690.0f, -800.0f, 0.0f), Vector3(350.0f, 1000.0f, 200.0f));//出生点右的墙
	Wall* wall2 = new Wall(Vector3(1040.0f, -800.0f, 0.0f), Vector3(650.0f, 2000.0f, 200.0f));//出生点右的墙
	//auto wall3 = std::make_unique<Wall>(Vector3(0.0f, 250.0f, 0.0f), Vector3(2000.0f, 600.0f, 100.0f));//出生点后的墙
	Wall* wall3 = new Wall(Vector3(0.0f, 500.0f, 0.0f), Vector3(2000.0f, 1000.0f, 100.0f));//出生点后的墙
	//auto wall4 = std::make_unique<Wall>(Vector3(0.0f, -950.0f, 0.0f), Vector3(2000.0f, 600.0f, 100.0f));//出生点后的墙
	Wall* wall4 = new Wall(Vector3(0.0f, -1500.0f, 0.0f), Vector3(2000.0f, 1000.0f, 80.0f));//出生点前的墙
	ObjectManager::Instance()->AddObjectBy(wall);
	ObjectManager::Instance()->AddObjectBy(wall2);
	ObjectManager::Instance()->AddObjectBy(wall3);
	ObjectManager::Instance()->AddObjectBy(wall4);

}

void Game::onInput(char* keys, char* prekeys)
{
	if (keys[DIK_BACKSPACE] && !prekeys[DIK_BACKSPACE])
	{
		SceneManager::Instance()->switchScene(SceneManager::SceneType::Title);
	}
	CharactorManager::Instance()->onInput(keys, prekeys);
	//m_camera.Input(keys);
}

void Game::Update()
{
	m_camera.Update();

	ObjectManager::Instance()->Update();
	CollisionManager::Instance()->ProcessCollision();


	if (!isOver)
	{
		if(CharactorManager::Instance()->GetPlayer()->GetIsDead() || CharactorManager::Instance()->GetSnake()->GetIsDead())
		{
			isOver = true;
			SceneManager::Instance()->DelayedSwitchScene(SceneManager::SceneType::Title, 3.0f);
		}
	}
	
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

void Game::Draw(const Camera& camera)
{
	Novice::DrawBox(0, 0, (int)windowWidth, (int)windowHeight, 0.0f, backColor, kFillModeSolid);
	ObjectManager::Instance()->Draw(camera);
//#ifdef _DEBUG
	//CollisionManager::Instance()->onDebugRender(camera);
//#endif // DEBUG
	Novice::DrawBox(0, 0, (int)windowWidth, (int)windowHeight, 0.0f, frontColor, kFillModeSolid);
}

void Game::onExit()
{
	m_camera.Reset();
	CharactorManager::Instance()->RemoveAllCharactors();
	ObjectManager::Instance()->RemoveAllObject();

}
