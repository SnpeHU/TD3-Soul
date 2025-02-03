#include "BlockEmiiter.h"
#include "BlockParticle.h"

BlockEmitter::BlockEmitter(Vector3 pos, float emitInterval)
{
	name = "BlockEmitter";
	this->pos = pos;
	this->emitInterval = emitInterval;
	size = { 50.0f,50.0f };

	//emitTimer
	emitTimer.set_one_shot(false);
	emitTimer.set_wait_time(emitInterval);
	emitTimer.set_on_timeout([this]() {
		//emit
		//在30-150度之间随机生成的发射角度
		float angle = 30.0f + (rand() % 120);

		//随机取lifeTime在0.3-0.5之间
		float lifeTime = 0.3f + (rand() % 30) / 100.0f;


		//将角度转换为弧度
		float theta = angle * (PI / 180.0f);
		//计算出发射方向
		Vector3 dir = { cos(theta),0.0f,sin(theta) };

		//ObjectManager::Instance()->AddObjectBy(new BlockParticle(this->pos, dir, 0.5f));

		//根据Emiiter的size随机偏移位置 
		float offsetX = (rand() % (int)size.x) - size.x / 2;
		float offsetY = (rand() % (int)size.y) - size.y / 2;


		Vector3 posB = this->pos;
		posB.x += offsetX;
		posB.y += offsetY;
		float angleOffset = 0.0f;
		//当生成粒子的位置的偏移量越大，角度越大
		if (offsetX > 0)
		{
			angleOffset = 90.0f * (1.0f -  offsetX/(size.x/2));
		}
		else
		{
			angleOffset = 90.0f * (1.0f +  (-offsetX) / (size.x / 2));
		}
		//将角度转换为弧度
		float thetaOffset = angleOffset * (PI / 180.0f);
		//计算出发射方向
		Vector3 dirOffset = { cos(thetaOffset),0.0f,sin(thetaOffset) };

		//BlockParticle* newParB = new BlockParticle(posB, dirOffset, 0.3f);
		ObjectManager::Instance()->AddObjectBy(new BlockParticle(posB, dirOffset, lifeTime));

		});
		

}

BlockEmitter::BlockEmitter(Vector3 _pos, float _emitInterval, Vector2 _particleSize, Vector3 _particleToward, Vector3 _particleAcceleration, float _particleLifeTime, float _particleSpeed, float _rotateSpeed,int _particleColor)
{
	name = "BlockEmitter";
	this->pos = _pos;
	this->emitInterval = _emitInterval;
	this->parSize = _particleSize;
	this->parToward = _particleToward;
	this->parAcc = _particleAcceleration;
	this->parSpeed = _particleLifeTime;
	this->parLifeTime = _particleSpeed;
	this->rotateSpeed = _rotateSpeed;
	this->parColor = _particleColor;
	//emitTimer
	emitTimer.set_one_shot(false);
	emitTimer.set_wait_time(emitInterval);
	emitTimer.set_on_timeout([this]() {
		//emits
		//BlockParticle>(pos,particleSize,particleToward,particleAcceleration,particleSpeed,particleLifeTime,particleColor);	
		BlockParticle* newPar = new BlockParticle(pos, parSize, parToward, parAcc, parSpeed, parLifeTime, rotateSpeed, parColor);
		ObjectManager::Instance()->AddObjectBy(newPar);
		});
}

void BlockEmitter::Update()
{
	Emitter::Update();
}

void BlockEmitter::Draw(const Camera& camera)
{
	(void)camera;
	//for (auto& particle : particles)
	//{
	//	particle->Draw(camera);
	//}
}
