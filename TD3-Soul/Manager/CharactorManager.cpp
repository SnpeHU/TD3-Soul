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

	auto newSnake = std::make_unique<Snake>(Vector3(0, -800, 0));
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
	if (keys[DIK_R] && !prekeys[DIK_R])
	{
		RespwanAll();
	}
}

void CharactorManager::Update()
{
	//player->Update();
	CheckCharactorsLive();
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

void CharactorManager::RespwanPlayer()
{
	if (player)
	{
		ObjectManager::Instance()->RemoveObject(player);
	}
	auto newPlayer = std::make_unique<Player>(Vector3(0, 0, 0));
	player = newPlayer.get();
	ObjectManager::Instance()->AddObject(std::move(newPlayer));
}

void CharactorManager::RespwanPlayer(Vector3 pos)
{
	if (player)
	{
		ObjectManager::Instance()->RemoveObject(player);
	}
	auto newPlayer = std::make_unique<Player>(pos);
	player = newPlayer.get();
	ObjectManager::Instance()->AddObject(std::move(newPlayer));
}

void CharactorManager::RespwanSnake()
{
	if (snake)
	{
		ObjectManager::Instance()->RemoveObject(snake);
	}
	auto newSnake = std::make_unique<Snake>(Vector3(0, -200, 0));
	snake = newSnake.get();
	ObjectManager::Instance()->AddObject(std::move(newSnake));
}

void CharactorManager::RespwanAll()
{
	if (player)
	{
		ObjectManager::Instance()->RemoveObject(player);
	}
	
	//auto newPlayer = std::make_unique<Player>(Vector3(0, 0, 0));
	//player = newPlayer.get();

	if (snake) {
		ObjectManager::Instance()->RemoveObject(snake);
	}
	auto newSnake = std::make_unique<Snake>(Vector3(0, -200, 0));
	snake = newSnake.get();

	player = new Player(Vector3(0, 0, 0));

	ObjectManager::Instance()->AddObjectBy(player);
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
