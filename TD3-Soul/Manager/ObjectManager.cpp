#include "ObjectManager.h"
#include <algorithm>

ObjectManager* ObjectManager::manager = nullptr;

ObjectManager* ObjectManager::Instance()
{
	if (!manager)
	{
		manager = new ObjectManager();
	}
	return manager;
}

void ObjectManager::Update()
{
	//根据Y轴排序
	std::sort(objects.begin(), objects.end(), [](const std::unique_ptr<Object>& a, const std::unique_ptr<Object>& b) {
		return a->GetPos().y < b->GetPos().y;
	});

	for (auto& object : objects)
	{
		object->Update();
	}
}

void ObjectManager::Draw(const Camera& camera)
{
	for (auto& object : objects)
	{
		object->Draw(camera);
	}
}

void ObjectManager::AddObject(std::unique_ptr<Object> object)
{
	objects.push_back(std::move(object));
}
