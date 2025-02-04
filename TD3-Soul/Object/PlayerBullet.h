#pragma once
#include "Bullet.h"
#include "State/StateMachine.h"
class BlockEmitter;
class PlayerBullet : public Bullet
{
public:
	enum class BulletState
	{
		FollowPlayer,
		Aim,
		Shooted,
	};

	PlayerBullet(Vector3 pos);
	~PlayerBullet();
	void Update() override;
	void Draw(const Camera& camera) override;

	void switchState(BulletState state);

	BulletState getState() const { return curstate; };

	float getRotateAngle() const { return rotateAngle; };
	void setRotateAngle(float angle) { rotateAngle = angle; };

	float getshakePosZ() const { return shakePosZ; };
	void setshakePosZ(float z) { shakePosZ = z; };

	//getStaeMachine
	StateMachine& getStateMachine() { return stateMachine; };

	bool getIsCanBack() const { return isCanBack; };
	void setIsCanBack(bool flag) { isCanBack = flag; };

	bool getIsCanPick() const { return isCanPick; };
	void setIsCanPick(bool flag) { isCanPick = flag; };

	bool getIsRebound() const { return isRebound; };
	void setIsRebound(bool flag) { isRebound = flag; };

	bool getIsCanShoot() const { return isCanShoot; };
	void setIsCanShoot(bool flag) { isCanShoot = flag; };

	bool getIsCanDamage() const { return isCanDamage; };
	void setIsCanDamage(bool flag) { isCanDamage = flag; };

private:

	float kAirResistance = 0.04f;
	

	float rotateRadius = 30.0f;
	float rotateAngle = 0.0f;

	Vector3 rotateCenter;

	float shakePosZ = 0.0f;

	BulletState curstate = BulletState::FollowPlayer;
	StateMachine stateMachine;

	bool isCanBack = false;//是否可以回收
	bool isCanPick = false;//是否可以拾取
	bool isRebound = true;//是否可以反弹
	bool isCanShoot = false;//是否可以发射
	bool isCanDamage = false;//是否可以造成伤害

	//std::unique_ptr<BlockEmitter> tailEmitter = nullptr;
	BlockEmitter* tailEmitter = nullptr;

};
