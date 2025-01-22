#include "collision_manager.h"
#include <Novice.h>
#include "Object/Object.h"

using namespace std;
CollisionManager* CollisionManager::manager = nullptr;
CollisionManager* CollisionManager::Instance()
{
    if (manager == nullptr)
    {
		manager = new CollisionManager();
	}
    return manager;
}

CollisionBox* CollisionManager::CreatCollisionBox(Object* owner)
{
    CollisionBox* collisionBox = new CollisionBox(owner);
    collisionbox_list.push_back(collisionBox);
    return collisionBox;
}

    
    

void CollisionManager::DestroyCollisionBox(CollisionBox* collisionBox)
{
    //checknullptr
    if (collisionBox == nullptr)
    {
        return;
    }
    collisionbox_list.erase(std::remove(collisionbox_list.begin(), collisionbox_list.end(), collisionBox), collisionbox_list.end());
    delete collisionBox;
    

}

//处理玩家与敌人之间的碰撞
void CollisionManager::ProcessCollision()
{
    for (CollisionBox* collisionbox_src : collisionbox_list)
    {
        //自身が無効または自身のレイヤーがNoneの場合はスキップ
        if (!collisionbox_src->enabled || collisionbox_src->layer_dest.empty())
        {
            continue;
        }

        for (CollisionBox* collisionbox_dest : collisionbox_list)
        {
            //排除不启用的碰撞盒，自身的碰撞盒
            //無効、自身ボックスを除く
            if (!collisionbox_dest->enabled || collisionbox_src == collisionbox_dest
                /*|| collisionbox_src->layer_dest != collisionbox_dest->layer_src*/)
            {
                continue;
            }

			//检查是否有对应的层
			//対応するレイヤーがあるかどうか
			auto it = collisionbox_src->layer_dest.find(collisionbox_dest->layer_src);
            if (it == collisionbox_src->layer_dest.end())
            {
                continue;
            }

            //衝突判定
            bool isCollideX = (max(collisionbox_src->pos.x + collisionbox_src->size.x / 2, collisionbox_dest->pos.x + collisionbox_dest->size.x / 2)
                - min(collisionbox_src->pos.x - collisionbox_src->size.x / 2, collisionbox_dest->pos.x - collisionbox_dest->size.x / 2)
                <= collisionbox_src->size.x + collisionbox_dest->size.x);

            bool isCollideY = (max(collisionbox_src->pos.y + collisionbox_src->size.y / 2, collisionbox_dest->pos.y + collisionbox_dest->size.y / 2)
                - min(collisionbox_src->pos.y - collisionbox_src->size.y / 2, collisionbox_dest->pos.y - collisionbox_dest->size.y / 2)
                <= collisionbox_src->size.y + collisionbox_dest->size.y);

			bool isCollid = fabs(collisionbox_src->pos.z - collisionbox_dest->pos.z) <= 10.0f;

            if (isCollideX && isCollideY)
            {
				it->second();
                
				//如果是地图层，调整位置
				//マップレイヤーの場合、位置を調整
                if (collisionbox_dest->layer_src == CollisionLayer::Map)
                {
                    collisionbox_src->owner->SetPos(Vector3(0,0,0));

                }
            }
        }

    }
}

void CollisionManager::onDebugRender()
{
    for(CollisionBox* collisionbox : collisionbox_list)
    {
		int linecolor = collisionbox->enabled? 0xFFA500FF : GREEN;

        Novice::DrawBox(static_cast<int>(collisionbox->pos.x - collisionbox->size.x / 2), static_cast<int>(collisionbox->pos.y + collisionbox->size.y / 2),
            static_cast<int>(collisionbox->size.x), static_cast<int>(collisionbox->size.y), 0.0f, linecolor, kFillModeWireFrame);
        
    }
    
    
}

void CollisionManager::onDebugRender(const Camera& camera)
{
	for (CollisionBox* collisionbox : collisionbox_list)
	{
        // 获取摄像机矩阵
        Matrix3x3 cameraMatrix = camera.GetCameraMatrix();
        // 将对象的世界坐标转换为屏幕坐标
        Vector2 screenPos = TransformFrom3D(pos, cameraMatrix, camera.heightscale);
		int linecolor = collisionbox->enabled ? 0xFFA500FF : GREEN;

		Novice::DrawBox(static_cast<int>(collisionbox->pos.x - collisionbox->size.x / 2), static_cast<int>(collisionbox->pos.y + collisionbox->size.y / 2),
			static_cast<int>(collisionbox->size.x), static_cast<int>(collisionbox->size.y), 0.0f, linecolor, kFillModeWireFrame);
	}
}

