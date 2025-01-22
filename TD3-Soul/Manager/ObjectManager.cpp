#include "ObjectManager.h"
#include <algorithm>
#ifdef _DEBUG
#include<imgui.h>
#endif // DEBUG
ObjectManager* ObjectManager::manager = nullptr;

ObjectManager* ObjectManager::Instance()
{
	if (!manager)
	{
		manager = new ObjectManager();
	}
	return manager;
}

void ObjectManager::DestroyInstance()
{
	if (manager)
	{
		delete manager;
		manager = nullptr;
	}
}

void ObjectManager::Init()
{
}

void ObjectManager::Update()
{
	//根据Y轴排序
	std::sort(objects.begin(), objects.end(), [](const std::shared_ptr<Object>& a, const std::shared_ptr<Object>& b) {
		return a->GetPos().y > b->GetPos().y;
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
#ifdef _DEBUG
	for (auto& object : objects)
	{
		object->DrawDebug(camera);
	}
	ImGui::Begin("Objects");
	ImGui::Text("Object Count: %d", objects.size());
	for (auto& object : objects)
	{
		ImGui::Text(object->name.c_str());
		
	}
	ImGui::End();
#endif // DEBUG
}

void ObjectManager::AddObject(std::shared_ptr<Object> object)
{
	objects.push_back(object);
}

void ObjectManager::RemoveObject(std::shared_ptr<Object> object)
{
	auto it = std::find_if(objects.begin(), objects.end(), [object](const std::shared_ptr<Object>& obj) {
		return obj == object;
	});
	if (it != objects.end())
	{
		objects.erase(it);
	}
}
