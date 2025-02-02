#include "PlayerBulletState.h"
#include "Manager/CharactorManager.h"
#include "Object/PlayerBullet.h"

#pragma region FollowState
FollowState::FollowState(PlayerBullet* owner)
{
	this->owner = owner;
	name = "Follow";
}
void FollowState::onEnter()
{
	owner->getHurtBox()->setEnabled(false);
	owner->switchState(PlayerBullet::BulletState::FollowPlayer);
	owner->setIsCanBack(false);
	owner->SetVelocity({ 0.0f,0.0f,0.0f });
}
void FollowState::onUpdate()
{
	

}
void FollowState::onExit()
{
}
#pragma endregion

#pragma region AimState
AimState::AimState(PlayerBullet* owner)
{
	this->owner = owner;
	name = "Aim";
	aimTimer.set_one_shot(false);
	aimTimer.set_wait_time(currentTime);
	aimTimer.set_on_timeout([=]()
		{
			if (powerLevel < maxPowerLevel)
			{
				powerLevel++;
				if (powerLevel == 1)
				{
					owner->setIsCanShoot(true);
				}

			}
			currentTime += increTime;
			aimTimer.set_wait_time(currentTime);
		});
}
void AimState::onEnter()
{
	owner->switchState(PlayerBullet::BulletState::Aim);
}
void AimState::onUpdate()
{
	aimTimer.on_update(deltaTime);

	
}
void AimState::onExit()
{
	aimTimer.restart();
	//子弹速度等于玩家朝向* （基础速度 + 力量等级的2次方
	Vector3 vel = owner->GetToward() * (basicspeed + powf(3, (float)powerLevel));
	/*Vector3 vel = owner->GetToward() * (basicspeed + );*/
	owner->SetVelocity(vel);
	powerLevel = 0;
	currentTime = minTime;
	
	
}
#pragma endregion

#pragma region ShootedState
ShootedState::ShootedState(PlayerBullet* owner)
{
	this->owner = owner;
	name = "Shooted";
}
void ShootedState::onEnter()
{

	owner->getHurtBox()->setEnabled(true);
	owner->setIsCanShoot(false);

	owner->switchState(PlayerBullet::BulletState::Shooted);
	pickTimer.set_one_shot(true);
	pickTimer.set_wait_time(pickTime);
	pickTimer.set_on_timeout([&]()
		{
			owner->setIsCanPick(true);
		});
}
void ShootedState::onUpdate()
{
	pickTimer.on_update(deltaTime);
}
void ShootedState::onExit()
{
	pickTimer.restart();
	
	owner->setIsCanPick(false);
	owner->setIsRebound(true);
}
#pragma endregion