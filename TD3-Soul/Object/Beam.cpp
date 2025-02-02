#include "Beam.h"
#include "Manager/CharactorManager.h"
#include "Emitter/BlockParticle.h"
#include "Emitter/BlockEmiiter.h"
Beam::Beam(Vector3 _endPos, Vector3 _startPos,Charactor* _target)
{
	this->pos = _endPos;//光束落点位置
	this->startPos = _startPos;//光束发射位置
	this->target = _target;
	size = { 40.0f,40.0f };
	color = 0x8B3A3AFF;

	speed = 3.0f;
	maxSpeed = 8.0f;

	hurt_box = CollisionManager::Instance()->CreatCollisionBox(this);
	hurt_box->setLayerSrc(CollisionLayer::EnermyBullet);
	hurtBoxSize = { size.x,size.y / 2 };
	hurt_box->setSize(hurtBoxSize);


	toGroundTimer.set_one_shot(true);
	toGroundTimer.set_wait_time(0.5f);
	toGroundTimer.set_on_timeout([this]() {
		isToGround = true;
		});

	emitTimer.set_one_shot(false);
	emitTimer.set_wait_time(emitInterval);
	emitTimer.set_on_timeout([this]() {
		//for (auto& point : points)
		//{
		//	ObjectManager::Instance()->AddObjectBy(new BlockParticle(point, Vector2{ 20.0f,20.0f }, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.4f), 0.0f, 1.0f, color));
		//}

		//每次发射三个节点的粒子,
		for (size_t i = 0; i < emitCount; i++)
		{
			ObjectManager::Instance()->AddObjectBy(new BlockParticle(points[emitIndex], parSize, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 0.0f, 1.0f, color,0.3f));
			emitIndex++;
			if (emitIndex >= points.size() - 1)
			{
				emitIndex = 0;
			}
		}

		});

	blockEmitter = std::make_unique<BlockEmitter>(pos, 0.05f);
	blockEmitter->SetEnable(false);
}

void Beam::Update()
{
	length = (pos - startPos).length();
	curLength = length;

	//if (!isToGround)
	//{
	//	
	//	//实现easeInCubic更新当前长度


	//	//curLength = easeInCubic(toGroundTimer.get_progress(), 0.0f, length, 1.0f);
	//	toGroundTimer.on_update(deltaTime);
	//}
	//Vector3 dir = (target->GetPos() - pos).normalize();

	//在starPos和endPos之间生成粒子,每隔linkSize的距离生成一个粒子


	
	nodeCount = int(curLength / linkSize);
	//实时更新节点数量
	if (nodeCount > points.size())
	{
		for (size_t i = points.size(); i < nodeCount; i++)
		{
			points.push_back(Vector3::lerp(startPos, pos, i / float(nodeCount)));
		}
	}
	else if (nodeCount < points.size())
	{
		points.erase(points.begin() + nodeCount, points.end());
	}

	for (int i = 0; i < nodeCount; i++)
	{
		points[i] = Vector3::lerp(startPos, pos, i / float(nodeCount));
	}

	emitTimer.on_update(deltaTime);

	blockEmitter->Update();
	blockEmitter->SetPos(pos);

	Bullet::Update();
}

void Beam::Draw(const Camera& camera)
{
	Object::Draw(camera);
	
	/*Novice::Dra*/
}
	
	
