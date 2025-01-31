#include "CircleEmitter.h"
#include "CircleParticle.h"
CircleEmitter::CircleEmitter(Vector3 pos, float emitInterval)
{
	this->pos = pos;
	this->emitInterval = emitInterval;
	size = { 0.0f,0.0f };
	//emitTimer
	emitTimer.set_one_shot(false);
	emitTimer.set_wait_time(emitInterval);
	emitTimer.set_on_timeout([this]() {
		//emit
		CircleParticle* newParticle = new CircleParticle(this->pos, 0.6f, 0.8f);
		particles.push_back(newParticle);
		});
}

void CircleEmitter::Update()
{
	Emitter::Update();
}

void CircleEmitter::Draw(const Camera& camera)
{
	for (auto& particle : particles)
	{
		particle->Draw(camera);
	}
}
