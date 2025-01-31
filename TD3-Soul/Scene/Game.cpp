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
	CharactorManager::Instance()->RemoveAllCharactors();
	ObjectManager::Instance()->RemoveAllObject();

	CharactorManager::Instance()->RespwanSnake();
	CharactorManager::Instance()->RespwanPlayer();
	m_camera.SetTarget(CharactorManager::Instance()->GetPlayer().get());

	//ロードマップ
	auto wall = std::make_shared<Wall>(Vector3(-800.0f, -800.0f, 0.0f), Vector3(1000.0f, 1000.0f, 100.0f));//出生点左的墙
	auto wall2 = std::make_shared<Wall>(Vector3(800.0f, -800.0f, 0.0f), Vector3(1000.0f, 1000.0f, 100.0f));//出生点右的墙
	auto wall3 = std::make_shared<Wall>(Vector3(0.0f, 200.0f, 0.0f), Vector3(3000.0f, 1000.0f, 100.0f));//出生点后的墙
	auto bossRoomLeftWall = std::make_shared<Wall>(Vector3(-800.0f, -800.0f, 0.0f), Vector3(1000.0f, 1000.0f, 100.0f));//出生点左的墙
	ObjectManager::Instance()->AddObject(wall);
	ObjectManager::Instance()->AddObject(wall2);
	ObjectManager::Instance()->AddObject(wall3);

	//auto blockEmitterA = std::make_shared<BlockEmitter>(Vector3(0.0f, 30.0f, 0.0f),0.01f);
	//blockEmitter = blockEmitterA.get();
	//
	//ObjectManager::Instance()->AddObject(blockEmitterA);

	auto circleEmitterA = std::make_shared<CircleEmitter>(Vector3(30.0f, 0.0f, 0.0f), 0.2f);
	circleEmitter = circleEmitterA.get();

	ObjectManager::Instance()->AddObject(circleEmitterA);




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

	if (Novice::IsTriggerMouse(0))
	{
		//blockEmitter->SetEnable(!blockEmitter->GetEnable());
		circleEmitter->SetEnable(!circleEmitter->GetEnable());
	};
	
	CollisionManager::Instance()->ProcessCollision();
	ObjectManager::Instance()->Update();

	if (CharactorManager::Instance()->GetPlayer()->GetIsDead())
	{
		CharactorManager::Instance()->RespwanAll();
		m_camera.SetTarget(CharactorManager::Instance()->GetPlayer().get());

	}
	

}

void Game::Draw(const Camera& camera)
{
	ObjectManager::Instance()->Draw(camera);
	//CollisionManager::Instance()->onDebugRender(camera);
}

void Game::onExit()
{
	m_camera.Reset();
	CharactorManager::Instance()->RemoveAllCharactors();
	ObjectManager::Instance()->RemoveAllObject();
}
