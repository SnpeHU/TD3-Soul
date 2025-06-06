#pragma once
#include <memory>
#include <vector>
#include "Object/Object.h"
//根据Y坐标排序
class ObjectManager
{
public:
	static ObjectManager* Instance();
	void DestroyInstance();
	void Init();
	void Update();
	void Draw(const Camera& camera);

	void AddObject(std::unique_ptr<Object> object);
	void AddObjectBy(Object* object);
	//void RemoveObject(std::unique_ptr<Object> object);
	void RemoveObject(Object* object);
	void RemoveAllObject();
private:
	ObjectManager() = default;
	~ObjectManager() = default;

private:
	static ObjectManager* manager;

	std::vector<std::unique_ptr<Object>> objects;
	//std::vector<Object*> objects;

};
