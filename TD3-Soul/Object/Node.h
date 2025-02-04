#pragma once
#include <Object/Charactor.h>
#include <Tool/MyVector3.h>
class Node : public Charactor
{
public:
	Node(Vector3 pos);
	~Node() = default;

	void Update() override;
	void Draw(const Camera& camera) override;

	void setCanHurt(bool flag) { isCanHurt = flag; };
	bool getCanHurt() const { return isCanHurt; };

	void SetIsDestroyed(bool flag) { isDestroyed = flag; };
	bool GetIsDestroyed() const { return isDestroyed; };

	bool isHead = false;
	bool isHeart = false;

private:
	
	//Vector2 size;
	Vector2 drawPos;

	int bordercolor;
	int boderwidth;

	bool isCanHurt = false;
	bool isDestroyed = false;

	int hurtcolor;

	int heartcolor;
	int heartcolorA;
	int heartcolorB;

	Timer heartTimer;
	float heartTime = 0.2f;

	Timer heartIntervalTimer;
	float heartIntervalTime = 1.0f;

	bool isBeating = false;	
	int beatCount = 0;

	//Vector2 mouseSize = { 10.0f,10.0f };
	//Vector2 mousePos = {0.0f,size.y/2};
	
	int impactAudio = Novice::LoadAudio("./rs/impact.wav");
};
