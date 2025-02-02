#pragma once
#include <string>
using std::string;
class Camera;
class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void onEnter() {}//シーンに入るときに呼び出される
	virtual void onInput(char* keys, char* prekeys) = 0;

	virtual void Update() = 0;
	virtual void Draw(const Camera& camera) = 0;
	virtual void onExit() = 0;//シーンが切り替わるときに呼ばれる

public:
	string s_name = "none";
	int backColor = 0xEFF0E6FF;
	float windowWidth = 1280.0f;
	float windowHeight = 720.0f;

	int frontColor = 0x00000000;//滤镜颜色
};
