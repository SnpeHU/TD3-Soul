#pragma once
#include "Object/Charactor.h"
#include <memory>
class CharactorManager
{
public:
	static CharactorManager* Instance();


	void Init();
	void onInput(char* keys, char* prekeys);
	void Update();

	void Draw(/*const Camera& camera*/);

private:
	CharactorManager();
	~CharactorManager();

private:
	static CharactorManager* manager;

	Charactor* player = nullptr;
};
