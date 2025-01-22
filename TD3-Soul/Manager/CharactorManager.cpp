#include "CharactorManager.h"
#include "ObjectManager.h"

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
	auto newPlayer = std::make_shared<Player>(Vector3(0,0,0));
	player = newPlayer;
	ObjectManager::Instance()->AddObject(newPlayer);

	auto newSnake = std::make_shared<Snake>(Vector3(0, 0, 0));
	snake = newSnake;
	ObjectManager::Instance()->AddObject(newSnake);
}

void CharactorManager::onInput(char* keys, char* prekeys)
{
	player->Input(keys, prekeys);
	//snake->Input(keys, prekeys);
	if (keys[DIK_R] && !prekeys[DIK_R])
	{
		RespwanPlayer();
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
        player.reset();
    }
    if (snake && snake->GetCanRemove())
    {
        ObjectManager::Instance()->RemoveObject(snake);
        snake.reset();
    }
}

void CharactorManager::RespwanPlayer()
{
	ObjectManager::Instance()->RemoveObject(player);
	auto newPlayer = std::make_shared<Player>(Vector3(0, 0, 0));
	player = newPlayer;

	if (snake) {
		snake->ClearNodes(); // 清理蛇的Node对象
		ObjectManager::Instance()->RemoveObject(snake);
	}
	auto newSnake = std::make_shared<Snake>(Vector3(0, 0, 0));
	snake = newSnake;


	ObjectManager::Instance()->AddObject(newPlayer);
	ObjectManager::Instance()->AddObject(newSnake);
}

CharactorManager::CharactorManager()
{
}

CharactorManager::~CharactorManager()
{
	if (player)
	{
		ObjectManager::Instance()->RemoveObject(player);
		player.reset();
	}
	if (snake)
	{
		ObjectManager::Instance()->RemoveObject(snake);
		snake.reset();
	}
}
