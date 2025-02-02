#include "SceneManager.h"

SceneManager* SceneManager::manager = nullptr;

SceneManager* SceneManager::Instance()
{
	if (!manager)
	{
		manager = new SceneManager();
	}
	return manager;
}

void SceneManager::DestroyInstance()
{
	if (manager)
	{
		delete manager;
		manager = nullptr;
	}
}

void SceneManager::Init()
{
	tieleScene = new TitleScene();
	//clearSCene = new ClearScene();
	testScene = new TestScene();
	stageScene.push_back(new Game());
	setCurrentScene(stageScene[0]);


}


void SceneManager::onInput(char* keys, char* prekeys)
{
	currentScene->onInput(keys, prekeys);

}

void SceneManager::Update()
{
	if (isSwitchingScene)
	{
		switchSceneTimer.on_update(1.0f / 60.0f);
	}
	currentScene->Update();
}

void SceneManager::Draw(const Camera& camera)
{
	currentScene->Draw(camera);
}

void SceneManager::setCurrentScene(Scene* scene)
{
	currentScene = scene;
	currentScene->onEnter();
}

void SceneManager::switchScene(SceneType type)
{
	currentScene->onExit();
	switch (type)
	{
	case SceneManager::SceneType::Title:
		currentScene = tieleScene;
		break;
	case SceneManager::SceneType::Claer:
		currentScene = clearSCene;
		break;
	case SceneManager::SceneType::Game:
		currentScene = stageScene[selectedStage];
		break;
	case SceneManager::SceneType::Test:
		currentScene = testScene;
		break;
	default:
		break;
	}
	currentScene->onEnter();
}

void SceneManager::DelayedSwitchScene(SceneType type, float delay)
{
	if (isSwitchingScene)
	{
		return;
	}

	isSwitchingScene = true;
	switchSceneTimer.set_wait_time(delay);
	switchSceneTimer.set_one_shot(true);
	switchSceneTimer.set_on_timeout([this, type]() {
		switchScene(type);
		isSwitchingScene = false;
		});
	switchSceneTimer.restart();
}

SceneManager::~SceneManager()
{

		delete tieleScene;
		delete clearSCene;
		delete testScene;
		for (Scene* scene : stageScene)
		{
			delete scene;
		}
		stageScene.clear();

}
