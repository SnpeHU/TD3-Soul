#pragma once
#include <vector>
#include <memory>
#include "collision_box.h"

class Camera;
class CollisionManager {
public:
	static CollisionManager* Instance();

	CollisionBox* CreatCollisionBox(Object* owner);//作成

	//CollisionBox* CreatCollisionBox();//作成
	
	void DestroyCollisionBox(CollisionBox* collisionBox);//削除
	void DestroyAllCollisionBox();//全削除

	void ProcessCollision();//衝突判定処理流れ：条件判定→衝突判定→処理
	bool ShouldProcessCollision(CollisionBox* src, CollisionBox* dest);//衝突判定の条件
	bool CheckCollision(CollisionBox* src, CollisionBox* dest);//衝突判定
	void HandleCollision(CollisionBox* src, CollisionBox* dest);//レイヤーにより処理

	//void tileCollision(Charactor* charactor);//タイルとの衝突判定

	void onDebugRender();//デバッグ描画

	void onDebugRender(const Camera& camera);//デバッグ描画


private:
	static CollisionManager* manager;

	std::vector<CollisionBox*> collisionbox_list;

	//std::vector<std::vector<Tile>>* tiles = nullptr;
	
	CollisionManager() = default;
	~CollisionManager() = default;


};