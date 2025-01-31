#include "Emitter.h"
#include "Particle.h"
Emitter::~Emitter()
{
	for (auto& particle : particles)
	{
		delete particle;
	}
	particles.clear();
}
void Emitter::Update()
{
		
	if (isEnable)
	{
		emitTimer.on_update(deltaTime);

	}
	else
	{	//如果粒子为空，可以删除
		if (particles.size() == 0)
		{
			//isCanRemove = true;
		}
	}
		
		
		for (auto& particle : particles)
		{
			particle->Update();
		}


		particles.erase(std::remove_if(particles.begin(), particles.end(), [](Particle* particle) {
			return particle->GetCanRemove();
			}), particles.end());
}
