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
	// 根据Y轴排序
	std::sort(objects.begin(), objects.end(), [](const std::unique_ptr<Object>& a, const std::unique_ptr<Object>& b) {
		if (!a || !b) {
			return !a && b; // 将空指针排到前面
		}
		return a->GetPos().y > b->GetPos().y;
		});

	// 更新对象前先清理空指针
	objects.erase(std::remove_if(objects.begin(), objects.end(),
		[](const std::unique_ptr<Object>& obj) { return !obj; }), objects.end());

	// 更新对象
	for (auto& object : objects)
	{
		if (object && object.get() != nullptr) // 双重检查
		{
			try {
				object->Update();
			}
			catch (...) {
				// 标记为可删除而不是立即删除
				object->SetCanRemove(true);
			}
		}
	}

	// 删除标记为可删除的对象
	objects.erase(std::remove_if(objects.begin(), objects.end(), [](const std::unique_ptr<Object>& object) {
		return !object || object->GetCanRemove();
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
