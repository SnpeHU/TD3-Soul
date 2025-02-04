#include "Node.h"
#include <Manager/CharactorManager.h>
#include "Emitter/BlockParticle.h"
#include "Tool/Color.h"
Node::Node(Vector3 _pos)
{
	name = "Node";
	this->pos = _pos;
	size = { 30.0f,30.0f };
	drawPos = { 0.0f,size.y };
	color = 0x9E5C62FF;
	phasecolor = 0xb2444eFF;
	boderwidth = 3;
	hurtcolor = 0xc03844FF;

	heartcolorA = 0x9f424bFF;
	heartcolorB = 0xd53a48FF;

	isEnableGravity = false;
	gravity = 0.02f;

	hurt_box = CollisionManager::Instance()->CreatCollisionBox(this);
	hurt_box->setLayerSrc(CollisionLayer::Enemy);
	hurt_box->addLayerDest(CollisionLayer::PlayerBullet, [this]() {
		if (isCanHurt)
		{
			if (!CharactorManager::Instance()->GetSnake()->GetIsInvincible())
			{
				hurt_box->setEnabled(false);
				Novice::PlayAudio(impactAudio, 0, 1.0f);
				CharactorManager::Instance()->GetSnake()->SetIsInvincible(true);
				CharactorManager::Instance()->GetSnake()->aliveNodeNum--;
				for (int i = 0; i < 60; i++)
				{
					Vector3 parPos = { pos.x + rand() % int(size.x) - size.x / 2,pos.y + rand() % int(size.y) - size.y / 2,pos.z };
					Vector3 acc = { 0.0f,0.0f,float(rand() % 10) };

					float lifeTime = float(rand() % 100) / 100.0f;

					float pspeed = 0.0f;
					float rotateSpeed = 0.0f;
					int pcolor = color;
					auto newBlockParticle = std::make_unique<BlockParticle>(parPos, Vector2(5, 5), toward, acc, pspeed, lifeTime, rotateSpeed, pcolor);
					ObjectManager::Instance()->AddObject(std::move(newBlockParticle));
				}
				isDestroyed = true;
			}

		}
		});

	hurtBoxSize = { size.x * 2 - size.x/4,size.y };
	hurt_box->setSize(hurtBoxSize);

	heartIntervalTimer.set_one_shot(false);
	heartIntervalTimer.set_wait_time(heartIntervalTime);
	heartIntervalTimer.set_on_timeout([&]() {
		isBeating = true;

		});

	heartTimer.set_one_shot(false);
	heartTimer.set_wait_time(heartTime);
	heartTimer.set_on_timeout([&]() {
		beatCount++;
		if (beatCount > 2)
		{
			beatCount = 0;
			
			isBeating = false;
			
		}
		
		int temp = heartcolorA;
		heartcolorA = heartcolorB;
		heartcolorB = temp;
		});


}

void Node::Update()
{
	shadowSize = { (size.x + 8) * (1.0f - pos.z * 0.003f), (size.y - 5) * (1.0f - pos.z * 0.003f) };//影子大小更新
	Charactor::Update();
	if(!isDestroyed)
	{
		if (pos.z > 40.0f)
		{
			hurt_box->setEnabled(false);
		}
		else
		{
			hurt_box->setEnabled(true);
		}
	}
	toward = velocity.normalize();

	if (isHeart)
	{
		if (!isBeating)
		{
			heartIntervalTimer.on_update(deltaTime);
		}
		else
		{
			heartTimer.on_update(deltaTime);
			//让心跳颜色在a和b之间变化
			float t = heartTimer.get_progress();
			if (t > 1.0f)
			{
				t = 1.0f;
			}
			heartcolor = LerpColor(heartcolorA, heartcolorB, t);

		}
	}

}

void Node::Draw(const Camera& camera)
{
	if (!isDestroyed)
	{
		Object::Draw(camera);
		//Charactor::Draw(camera);
		Vector2 screenDrawPos = Transform(drawPos, objectMatrix);
		if (!isCanHurt)
		{
			Novice::DrawEllipse(int(screenDrawPos.x), int(screenDrawPos.y - pos.z * camera.heightscale), int(size.x), int(size.y), 0.0f, color, kFillModeSolid);
		}
		else
		{
			Novice::DrawEllipse(int(screenDrawPos.x), int(screenDrawPos.y - pos.z * camera.heightscale), int(size.x), int(size.y), 0.0f, hurtcolor, kFillModeSolid);
		}


		if (isHeart)
		{
			Novice::DrawEllipse(int(screenDrawPos.x), int(screenDrawPos.y - pos.z * camera.heightscale), int(size.x), int(size.y), 0.0f, heartcolor, kFillModeSolid);
		}

	}



}
