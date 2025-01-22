#pragma once
#include "Tool/MyVector2.h"
#include "Tool/MyVector3.h"
#include <functional>
#include "collision_layer.h"
#include <unordered_map>
class CollisionManager;
class Object;

class CollisionBox {

	friend CollisionManager;

public:
	void setEnabled(bool flag) {
		enabled = flag;
	}
	void setLayerSrc(CollisionLayer layer) {
		layer_src = layer;
	}
	
	void addLayerDest(CollisionLayer layer, std::function<void()> onCollide) {
		layer_dest[layer] = onCollide;
	}

	//const Vector2& getSize() const {
	//	return size;
	//}
	Vector2 getSize() const {
		return size;
	}
	void setSize(const Vector2& _size) {
		this->size = _size;
	}

	//const Vector2& getPos() const {
	//	return pos;
	//}
	Vector3 getPos() const {
		return pos;
	}
	void setPos(const Vector3& _pos) {
		this->pos = _pos;
	}
private:
	Vector2 size;
	Vector3 pos;//boxの中心座標
	bool enabled = true;
	//std::function<void()> onCollide;

	Object* owner = nullptr;


	CollisionLayer layer_src = CollisionLayer::None;//自身のレイヤー
	//CollisionLayer layer_dest = CollisionLayer::None;//衝突判定のレイヤー
	std::unordered_map<CollisionLayer, std::function<void()>> layer_dest;



	CollisionBox(Object* owner) : owner(owner) {}
	~CollisionBox() = default;

};