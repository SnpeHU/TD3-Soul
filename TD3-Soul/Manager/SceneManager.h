#pragma once
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <Scene/Scene.h>
#include <Scene/TitleScene.h>
//#include <ClearScene.h>
#include <Scene/Game.h>
#include <Scene/TestScene.h>
#include <vector>
#include <Tool/timer.h>
class SceneManager
{

public:
	static SceneManager* Instance();
	void DestroyInstance();
	enum class SceneType
	{
		Title,
		Claer,
		Game,
		Test,
		None
	};


	void Init();
	void onInput(char* keys, char* prekeys);
	void Update();

	void Draw(const Camera& camera);

	void setCurrentScene(Scene* scene);


	void switchScene(SceneType type);

	//setnextScene
	void setNextScene(SceneType type) { nextScene = type; }
	//getcurrentScene
	SceneType getCurrentSceneType() const { return nextScene; }

	void DelayedSwitchScene(SceneType type, float delay);


	Scene* getCurrentScene() const { return currentScene; }
	Timer& getSwitchSceneTimer() { return switchSceneTimer; }

	bool getIsSwitchingScene() const { return isSwitchingScene; }
	void setSwitchingScene(bool flag) { isSwitchingScene = flag; }

private:
	SceneManager() = default;
	~SceneManager();


private:

	static SceneManager* manager;


	Scene* currentScene = nullptr;

	SceneType nextScene = SceneType::None;

	

	Scene* tieleScene = nullptr;
	Scene* clearSCene = nullptr;
	Scene* testScene = nullptr;
	std::vector<Scene*> stageScene;
public:
	int stageNum = 2;//ステージの総数
	int selectedStage = 0;//選択されているステージ
	//Scene m_scene;

	Timer switchSceneTimer;
	bool isSwitchingScene = false;
};

#endif // !SCENEMANAGER_H