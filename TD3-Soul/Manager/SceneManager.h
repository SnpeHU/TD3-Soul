#pragma once
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <Scene/Scene.h>
#include <Scene/TitleScene.h>
//#include <ClearScene.h>
#include <Scene/Game.h>
#include <Scene/TestScene.h>
#include <vector>
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
		Test
	};


	void Init();
	void onInput(char* keys, char* prekeys);
	void Update();

	void Draw(const Camera& camera);

	void setCurrentScene(Scene* scene);


	void switchScene(SceneType type);

	Scene* getCurrentScene() const { return currentScene; }
private:
	SceneManager() = default;
	~SceneManager() = default;


private:

	static SceneManager* manager;


	Scene* currentScene = nullptr;
	

	Scene* tieleScene = nullptr;
	Scene* clearSCene = nullptr;
	Scene* testScene = nullptr;
	std::vector<Scene*> stageScene;
public:
	int stageNum = 2;//ステージの総数
	int selectedStage = 0;//選択されているステージ
	//Scene m_scene;


};

#endif // !SCENEMANAGER_H