#pragma once
#include "Object.h"
#include "Tool/Matrix.h"
#include "State/StateMachine.h"
class Charactor : public Object
{
public:
	//Charactor();
	virtual ~Charactor() = default;

	virtual void Input(char* keys, char* prekeys);
	virtual void Update() override;//不含节点角色的更新
	virtual void Draw(const Camera& camera) override;//无用

	void SwitchState(const std::string& _id);

	virtual void ClearNodes() {};

	bool GetIsDead() const { return isDead; };//只用于判断玩家和蛇主体的死亡

	void SetVelocity(Vector3 _velocity) { velocity = _velocity; };
	Vector3 GetVelocity() const { return velocity; };

	void SetAcceleration(Vector3 _acceleration) { acceleration = _acceleration; };
	Vector3 GetAcceleration() const { return acceleration; };


	bool GetIsOnGround() const { return isOnGround; };

	void SetEnableGravity(bool flag) { isEnableGravity = flag; };
	bool GetEnableGravity() const { return isEnableGravity; };

	void SetEnableResistance(bool flag) { isEnableResistance = flag; };
	bool getEnableResistance() const { return isEnableResistance; };


protected:
	//位置取角色底部中心
	Vector3 toward;
	Vector3 acceleration = {0.0f,0.0f,0.0f};
	Vector3 velocity = { 0.0f,0.0f,0.0f };;
	float speed;




	//默认为DrawBox的左上角
	Vector2 leftTop;
	
	bool isEnableGravity = false;
	float gravity = 0.6f;


	bool isEnableResistance = false;//是否启用摩擦力
	float kResistance = 0.1f;//摩擦力系数

	bool isOnGround = true;
	bool isDead = false;

	//状态机
	StateMachine stateMachine;


};
