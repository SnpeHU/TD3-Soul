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
	//根据Y轴排序 Y軸によって並べる
	std::sort(objects.begin(), objects.end(), [](const std::shared_ptr<Object>& a, const std::shared_ptr<Object>& b) {
		return a->GetPos().y > b->GetPos().y;
		//return (a->GetPos().y* a->GetPos().y + a->GetPos().z * a->GetPos().z) < (b->GetPos().y* b->GetPos().y + b->GetPos().z* b->GetPos().z);
	});

	for (auto& object : objects)
	{
		object->Update();
	}
	//删除标记为可删除的对象 削除可能なオブジェクトを削除する
	objects.erase(std::remove_if(objects.begin(), objects.end(), [](const std::shared_ptr<Object>& object) {
		return object->GetCanRemove();
		}), objects.end());
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

void ObjectManager::RemoveAllObject()
{
	objects.clear();
}
