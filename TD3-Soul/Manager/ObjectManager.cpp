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
    std::sort(objects.begin(), objects.end(), [](const std::unique_ptr<Object>& a, const std::unique_ptr<Object>& b) {
		//判断是否为空
		if (a == nullptr || b == nullptr)
		{
			return false;
		}
        return a->GetPos().y > b->GetPos().y;
    });

    // 更新对象
    for (auto& object : objects)
    {
		if (object) // Check if object is not null
		{
			object->Update();
		}
  
    }
	// 删除标记为可删除的对象 削除可能なオブジェクトを削除する
	objects.erase(std::remove_if(objects.begin(), objects.end(), [](const std::unique_ptr<Object>& object) {
		//判断是否为空
		if (object == nullptr)
		{
			return true;
		}
		return object->GetCanRemove();
		}), objects.end());

}

void ObjectManager::Draw(const Camera& camera)
{
	for (auto& object : objects)
	{

		if (object != nullptr)
		{
			object->Draw(camera);
		}

	}
#ifdef _DEBUG
	for (auto& object : objects)
	{
		if (object) // 检查对象是否为空
		{
			object->DrawDebug(camera);
		}

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

void ObjectManager::AddObject(std::unique_ptr<Object> object)
{
	objects.push_back(std::move(object));
}

void ObjectManager::AddObjectBy(Object* object)
{
	//objects.push_back(std::unique_ptr<Object>(object));
	objects.emplace_back(object);
}


void ObjectManager::RemoveObject(Object* object)
{
	auto it = std::find_if(objects.begin(), objects.end(),
		[object](const std::unique_ptr<Object>& obj) {
			return obj.get() == object;
		});

	if (it != objects.end()) {
		objects.erase(it);  // 删除目标对象
	}
	
}

void ObjectManager::RemoveAllObject()
{
	objects.clear();
}
