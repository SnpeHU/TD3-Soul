#pragma once
#include "Object/Charactor.h"
#include "Object/Player.h"
#include "Object/Snake.h"
#include "Object/Snake_D.h"
#include <memory>
class CharactorManager
{
public:
	static CharactorManager* Instance();

	void DestroyInstance();


	void Init();
	void onInput(char* keys, char* prekeys);
	void Update();
	//渲染在ObjectManager中，此处无视
	//ObjectManagerでレンダリングされますが、ここでは無視
	void Draw(/*const Camera& camera*/);



	void CheckCharactorsLive();
	void RespwanPlayer();
	void RespwanPlayer(Vector3 pos);
	void RespwanSnake();
	void RespwanAll();
	void RemoveAllCharactors();

	//void SetPlayer(std::shared_ptr<Charactor> _player) { player = _player; };
	std::shared_ptr<Player> GetPlayer() { return player; };

	std::shared_ptr<Snake> GetSnake() { return snake; };


private:
	CharactorManager();
	~CharactorManager();

private:
	static CharactorManager* manager;

	std::shared_ptr<Player> player = nullptr;
	std::shared_ptr<Snake> snake = nullptr;
	
	//Charactor* snake = nullptr;
};
