#include "BasicBullet.h"
#include "Emitter/BlockParticle.h"
#include <Manager/ObjectManager.h>
BasicBullet::BasicBullet(Vector3 pos, Vector3 _target)
{
	this->pos = pos;
	this->targetPos = _target;
	startPos = pos;

	size = { 200.0f,200.0f };

	color = 0x8B3A3AFF;

	hurt_box = CollisionManager::Instance()->CreatCollisionBox(this);
	hurt_box->setLayerSrc(CollisionLayer::Reducer);
	//hurt_box->addLayerDest(CollisionLayer::Map, [this]() {
	//	isCanRemove = true;
	//	});

	hurtBoxSize = { size.x,size.y};
	hurt_box->setSize(hurtBoxSize);
	hurt_box->setEnabled(false);

	moveTimer.set_one_shot(true);
	moveTimer.set_wait_time(moveltime);
	moveTimer.set_on_timeout([this]() {
		hurt_box->setEnabled(true);
		this->pos = targetPos;
		isArrive = true;

		});


	lifeTimer.set_one_shot(true);
	lifeTimer.set_wait_time(lifeTime);
	lifeTimer.set_on_timeout([this]() {
		isCanRemove = true;
		});
}

void BasicBullet::Update()
{
	shadowSize = {( 25 + 8) * (1.0f - pos.z * 0.003f), (25 - 5) * (1.0f - pos.z * 0.003f) };//影子大小更新

	if (!isArrive)
	{
		float t = moveTimer.get_progress();
		if (t > 1.0f)
		{
			t = 1.0f;
		}
		pos.x = (1 - t) * startPos.x + t * targetPos.x;
		pos.y = (1 - t) * startPos.y + t * targetPos.y;
		pos.z = (1 - t) * startPos.z + t * targetPos.z + jumpHeight * (1 - t) * t * 4;
		moveTimer.on_update(deltaTime);
	}
	else
	{
		lifeTimer.on_update(deltaTime);
	}

	if (hurt_box)
	{
		hurt_box->setPos(get_logic_center());
	}
	if (shadowSize.x < 0.0f)
	{
		shadowSize.x = 0.0f;
	}
	if (shadowSize.y < 0.0f)
	{
		shadowSize.y = 0.0f;
	}
}

void BasicBullet::Draw(const Camera& camera)
{
	if (!isArrive)
	{
		objectMatrix = camera.GetObjectMatrix(Vector2(pos.x, pos.y), 0.0f);
		Vector2 shadowPos = Transform(Vector2(0.0f, 0.0f), objectMatrix);

		Novice::DrawEllipse(int(shadowPos.x), int(shadowPos.y), int(shadowSize.x), int(shadowSize.y), 0.0f, shadowColor, kFillModeSolid);

		Vector2 screenDrawPos = Transform(Vector2(0.0f, 40.0f), objectMatrix);
		Novice::DrawEllipse(int(screenDrawPos.x), int(screenDrawPos.y - pos.z * camera.heightscale), int(20.0f), int(20.0f), 0.0f, color, kFillModeSolid);
	}
	else
	{
		//Vector2 screenDrawPos = Transform(Vector2(0.0f, 100.0f), objectMatrix);

			Vector3 parPos = { pos.x + rand() % int(size.x) - size.x / 2,pos.y + rand() % int(size.y),0.0f };
			Vector3 acc = { 0.0f,0.0f,float(rand() % 10 / 2) };
			float plifeTime = float(rand() % 100) / 100.0f;
			float pspeed = 0.0f;
			float rotateSpeed = 0.0f;
			int pcolor = color;
			auto newBlockParticle = std::make_unique<BlockParticle>(parPos, Vector2(5, 5), toward, acc, pspeed, plifeTime, rotateSpeed, pcolor);
			ObjectManager::Instance()->AddObject(std::move(newBlockParticle));
	}

}
