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

void CharactorManager::Init()
{
	

	auto newPlayer = std::make_unique<Charactor>();
	player = newPlayer.get();
	ObjectManager::Instance()->AddObject(std::move(newPlayer));
}

void CharactorManager::onInput(char* keys, char* prekeys)
{
	(void)keys;
	(void)prekeys;
}

void CharactorManager::Update()
{
}

void CharactorManager::Draw()
{
}

CharactorManager::CharactorManager()
{
}

CharactorManager::~CharactorManager()
{
}
