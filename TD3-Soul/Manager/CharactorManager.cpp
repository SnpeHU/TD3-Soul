#include "CharactorManager.h"
#include "ObjectManager.h"
extern Camera m_camera;
CharactorManager* CharactorManager::manager = nullptr;

CharactorManager* CharactorManager::Instance()
{
	if (!manager)
	{
		manager = new CharactorManager();
	}
	return manager;
}

void CharactorManager::DestroyInstance()
{
	if (manager)
	{
		delete manager;
		manager = nullptr;
	}
}

void CharactorManager::Init()
{
	auto newPlayer = std::make_unique<Player>(Vector3(0,0,0));
	player = newPlayer.get();
	ObjectManager::Instance()->AddObject(std::move(newPlayer));

	auto newSnake = std::make_unique<Snake>(Vector3(0, -200, 0));
	snake = newSnake.get();
	ObjectManager::Instance()->AddObject(std::move(newSnake));
}

void CharactorManager::onInput(char* keys, char* prekeys)
{
	if (player)
	{
		player->Input(keys, prekeys);
	}
	//snake->Input(keys, prekeys);
	//if (keys[DIK_R] && !prekeys[DIK_R])
//	{
		//player->Reset(Vector3(0, 0, 0));
		//snake->Reset(Vector3(0, -200, 0));
	//}
}

void CharactorManager::Update()
{
	//CheckCharactorsLive();
}

void CharactorManager::Draw()
{
}

void CharactorManager::CheckCharactorsLive()
{
    if (player && player->GetCanRemove())
    {
        ObjectManager::Instance()->RemoveObject(player);
		player = nullptr;
    }
    if (snake && snake->GetCanRemove())
    {
        ObjectManager::Instance()->RemoveObject(snake);
		snake = nullptr;
    }
}


void CharactorManager::RespwanPlayer(Vector3 pos)
{
	if (player)
	{
		ObjectManager::Instance()->RemoveObject(player);
		player = nullptr;
	}
	//auto newPlayer = std::make_unique<Player>(pos);
	
	player = new Player(pos);
	ObjectManager::Instance()->AddObjectBy(player);
	//m_camera.SetTarget(player);
}

void CharactorManager::RespwanSnake()
{
	if (snake)
	{
		ObjectManager::Instance()->RemoveObject(snake);
		snake = nullptr;
	}
	auto newSnake = std::make_unique<Snake>(Vector3(0, -200, 0));
	snake = newSnake.get();
	ObjectManager::Instance()->AddObject(std::move(newSnake));
	
}

void CharactorManager::RemoveAllCharactors()
{
	if (player)
	{
		ObjectManager::Instance()->RemoveObject(player);
		player = nullptr;
	}
	if (snake)
	{
		ObjectManager::Instance()->RemoveObject(snake);
		snake = nullptr;
	}
}

void CharactorManager::ResetPlayer(Vector3 pos)
{
	if (player)
	{
		player->Reset(pos);
	}
}

void CharactorManager::ResetSnake(Vector3 pos)
{
	if (snake)
	{
		snake->Reset(pos);
	}
}


CharactorManager::CharactorManager()
{
}

CharactorManager::~CharactorManager()
{
	if (player)
	{
		ObjectManager::Instance()->RemoveObject(player);
		player = nullptr;
	}
	if (snake)
	{
		ObjectManager::Instance()->RemoveObject(snake);
		snake = nullptr;
	}
}
