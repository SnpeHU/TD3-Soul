#include "collision_manager.h"
#include <Novice.h>
#include "Object/Object.h"
#include "Object/PlayerBullet.h"
#ifdef _DEBUG
#include<imgui.h>
#endif // DEBUG
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

void CollisionManager::DestroyAllCollisionBox()
{
	for (CollisionBox* collisionBox : collisionbox_list)
	{
		delete collisionBox;
	}
	collisionbox_list.clear();
}

//处理玩家与敌人之间的碰撞
void CollisionManager::ProcessCollision()
{
    for (CollisionBox* collisionbox_src : collisionbox_list)
    {

        for (CollisionBox* collisionbox_dest : collisionbox_list)
        {

            if (ShouldProcessCollision(collisionbox_src, collisionbox_dest) && CheckCollision(collisionbox_src, collisionbox_dest))
            {
                HandleCollision(collisionbox_src, collisionbox_dest);
            }
        }
    }
}

bool CollisionManager::ShouldProcessCollision(CollisionBox* src, CollisionBox* dest)
{
    // 检查 dest 是否是有效指针
    if (IsBadReadPtr(dest, sizeof(CollisionBox)))
    {
        return false;
    }
    //自身が無効または自身のレイヤーがないの場合はスキップ
    if (!src->enabled || src->layer_dest.empty() || !dest->enabled || src == dest)
    {
        return false;
    }
    //检查是否有对应的层
    //対応するレイヤーがあるかどうか
    auto it = src->layer_dest.find(dest->layer_src);
    if (it == src->layer_dest.end())
    {
        return false;
    }

    return true;
}

bool CollisionManager::CheckCollision(CollisionBox* src, CollisionBox* dest)
{
    bool isCollideX = (max(src->pos.x + src->size.x / 2, dest->pos.x + dest->size.x / 2)
        - min(src->pos.x - src->size.x / 2, dest->pos.x - dest->size.x / 2)
        <= src->size.x + dest->size.x);

    bool isCollideY = (max(src->pos.y + src->size.y / 2, dest->pos.y + dest->size.y / 2)
        - min(src->pos.y - src->size.y / 2, dest->pos.y - dest->size.y / 2)
        <= src->size.y + dest->size.y);
   
    bool isCollideZ = fabs(src->pos.z - dest->pos.z) <= 70.0f; //暂时仅判断z轴差值 一時的にZ軸の差のみを判定する

    return isCollideX && isCollideY && isCollideZ;
}

void CollisionManager::HandleCollision(CollisionBox* src, CollisionBox* dest)
{
    //如果是地图层，调整位置
    //マップレイヤーの場合、位置を調整
    if (dest->layer_src == CollisionLayer::Map)
    {
        Vector2 overlap = { (src->size.x + dest->size.x) / 2 - std::abs(src->pos.x - dest->pos.x),
                            (src->size.y + dest->size.y) / 2 - std::abs(src->pos.y - dest->pos.y) };
        if (overlap.x < overlap.y)//x轴碰撞
        {
            if (src->pos.x < dest->pos.x)
            {
                src->pos.x -= overlap.x;
            }
            else
            {
                src->pos.x += overlap.x;
            }

            if (src->layer_src == CollisionLayer::PlayerBullet)
            {
                PlayerBullet* bu = dynamic_cast<PlayerBullet*>(src->owner);
                if (bu->getIsRebound())
                {
                    bu->SetVelocity(Vector3(-bu->GetVelocity().x, bu->GetVelocity().y, 0.0f));
                }
            }
        }
        else//y轴碰撞
        {
            if (src->pos.y < dest->pos.y)
            {
                src->pos.y -= overlap.y;
            }
            else
            {
                src->pos.y += overlap.y;
            }

            if (src->layer_src == CollisionLayer::PlayerBullet)
            {
                PlayerBullet* bu = dynamic_cast<PlayerBullet*>(src->owner);
				if (bu->getIsRebound())//如果是玩家子弹，且子弹可以反弹 プレイヤーの弾且つ弾が跳ね返せる場合
                {
                    bu->SetVelocity(Vector3(bu->GetVelocity().x, -bu->GetVelocity().y, 0.0f));
                }
            }
        }
        src->owner->SetPos(Vector3(src->pos.x, src->pos.y - src->size.y / 2, src->pos.z));
    }

    //调用回调函数
    //コールバック関数を呼び出す
    auto it = src->layer_dest.find(dest->layer_src);
    if (it != src->layer_dest.end())
    {
        it->second();
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
		// 获取摄像机矩阵  カメラ行列を取得
        Matrix3x3 cameraMatrix = camera.GetCameraMatrix();
		// 将对象的世界坐标转换为屏幕坐标 オブジェクトのワールド座標をスクリーン座標に変換
        Vector2 screenPos = TransformFrom3D(collisionbox->pos, cameraMatrix, camera.heightscale);
		int linecolor = collisionbox->enabled ? 0xFFA500FF : GREEN;

		Novice::DrawBox(static_cast<int>(screenPos.x - collisionbox->size.x / 2), static_cast<int>(screenPos.y - collisionbox->size.y / 2),
			static_cast<int>(collisionbox->size.x), static_cast<int>(collisionbox->size.y), 0.0f, linecolor, kFillModeWireFrame);
	}

#ifdef _DEBUG
    ImGui::Begin("ColliBox");
    ImGui::Text("Object Count: %d", collisionbox_list.size());

    ImGui::End();
#endif // DEBUG
}

