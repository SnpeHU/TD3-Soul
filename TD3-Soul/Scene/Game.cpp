#include "Game.h"
#include "Manager/SceneManager.h"
#include "Manager/ObjectManager.h"
#include "Novice.h"
#include "Camera.h"
extern Camera m_camera;

Game::Game()
{
	s_name = "Game";
}

void Game::onEnter()
{
}

void Game::onInput(char* keys, char* prekeys)
{
	if (keys[DIK_BACKSPACE] && !prekeys[DIK_BACKSPACE])
	{
		SceneManager::Instance()->switchScene(SceneManager::SceneType::Title);
	}

	m_camera.Input(keys);
}

void Game::Update()
{
	m_camera.Update();
	ObjectManager::Instance()->Update();

}

void Game::Draw(const Camera& camera)
{
	ObjectManager::Instance()->Draw(camera);
}

void Game::onExit()
{
	m_camera.Reset();
}
