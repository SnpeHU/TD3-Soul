#include "BlockEmiiter.h"
#include "BlockParticle.h"
BlockEmitter::BlockEmitter(Vector3 pos, float emitInterval)
{
	this->pos = pos;
	this->emitInterval = emitInterval;
	size = { 20.0f,0.0f };

	//emitTimer
	emitTimer.set_one_shot(false);
	emitTimer.set_wait_time(emitInterval);
	emitTimer.set_on_timeout([this]() {
		//emit
		//在30-150度之间随机生成的发射角度
		float angle = 30.0f + (rand() % 120);

		//将角度转换为弧度
		float theta = angle * (PI / 180.0f);
		//计算出发射方向
		Vector3 dir = { cos(theta),0.0f,sin(theta) };



		//生成粒子
		BlockParticle* newParticle = new BlockParticle(this->pos, dir, 0.6f);
		particles.push_back(newParticle);

		//根据Emiiter的size随机偏移位置 
		float offsetX = (rand() % (int)size.x) - size.x / 2;


		Vector3 Posb = this->pos;
		Posb.x += offsetX;
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
		//生成粒子
		BlockParticle* newParticleOffset = new BlockParticle(Posb, dirOffset, 0.3f);
		particles.push_back(newParticleOffset);

		});
		

}

void BlockEmitter::Update()
{
	Emitter::Update();
}

void BlockEmitter::Draw(const Camera& camera)
{
	for (auto& particle : particles)
	{
		particle->Draw(camera);
	}
}
