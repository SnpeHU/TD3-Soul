#include "Beam.h"
#include "Manager/CharactorManager.h"
#include "Emitter/BlockParticle.h"
#include "Emitter/BlockEmiiter.h"
Beam::Beam(Vector3 _endPos, Vector3 _startPos,Charactor* _target)
{
	this->pos = _endPos;//光束落点位置
	this->startPos = _startPos;//光束发射位置
	this->target = _target;
	size = { 50.0f,50.0f };
	color = 0x8B3A3AFF;

	speed = 0.2f;//用于计算移动加速度
	maxSpeed = 6.0f;

	curLength = 0.0f;

	hurt_box = CollisionManager::Instance()->CreatCollisionBox(this);
	hurt_box->setLayerSrc(CollisionLayer::EnermyBullet);
	hurtBoxSize = { size.x,size.y / 2 };
	hurt_box->setSize(hurtBoxSize);
	hurt_box->setEnabled(false);


	toGroundTimer.set_one_shot(true);
	toGroundTimer.set_wait_time(1.0f);
	toGroundTimer.set_on_timeout([this]() {
		isToGround = true;
		hurt_box->setEnabled(true);
		blockEmitter = std::make_unique<BlockEmitter>(pos, 0.03f);
		blockEmitter->SetEnable(true);
		});

	emitTimer.set_one_shot(false);
	emitTimer.set_wait_time(emitInterval);
	emitTimer.set_on_timeout([this]() {

		//每次发射三个节点的粒子,
		for (size_t i = 0; i < emitCount; i++)
		{
			if (points.size() == 0)
			{
				break;
			}
			ObjectManager::Instance()->AddObjectBy(new BlockParticle(points[emitIndex], parSize, Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f, 0.3f,0.0f,color));
			emitIndex++;
			if (emitIndex >= points.size() - 1)
			{
				emitIndex = 0;
			}
		}
		//ObjectManager::Instance()->AddObjectBy(new BlockParticle(startPos, parSize, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 0.0f, 1.0f, 0.3f, 0.05f, color));

		});


}

void Beam::Update()
{
	length = (pos - startPos).length();
	

	if (!isToGround)
	{
		
		float t = toGroundTimer.get_progress();
		if (t > 1.0f)
		{
			t = 1.0f;
		}

		float easeInCubic = t * t * t;

		curLength = easeInCubic * length;
		
		toGroundTimer.on_update(deltaTime);
	}
	else
	{
		
		curLength = length;
		blockEmitter->Update();
		blockEmitter->SetPos(pos);

		//根据目标位置和当前位置计算方向
		Vector3 dir = (target->GetPos() - pos).normalize();
		acceleration = dir * speed;
	}

	if (velocity.length() > maxSpeed)
	{
		velocity = velocity.normalize() * maxSpeed;
	}


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

	//光束粒子
	emitTimer.on_update(deltaTime);

	Bullet::Update();
}

void Beam::Draw(const Camera& camera)
{
	Object::Draw(camera);
	
	/*Novice::Dra*/
}
	
	
