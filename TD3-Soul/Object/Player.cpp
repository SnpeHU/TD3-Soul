#include "Player.h"
#include "PlayerBullet.h"
#include "Novice.h"
#include "Manager/ObjectManager.h"
#ifdef _DEBUG
#include<imgui.h>
#endif // DEBUG

#define deltaTime (1.0f/60.0f)

Player::Player(Vector3 _pos)
{
	pos = _pos;
	toward = { 0.0f,0.0f ,0.0f};
	size = { 40.0f,40.0f };
	speed = 3.0f;

	leftTop = { -size.x / 2,size.y };

	shadowSize = { size.x/2 + 8,size.y/2 - 5 };

	curcolor = bodycolor;


	isDeBug = true;
	name = "Player";

	hp = maxHp;
	isDead = false;

	auto newPlayerBullet = std::make_unique<PlayerBullet>(pos);
	playerBullet = newPlayerBullet.get();
	ObjectManager::Instance()->AddObject(std::move(newPlayerBullet));

	//collisionbox
	hurt_box = CollisionManager::Instance()->CreatCollisionBox(this);
	hurt_box->setLayerSrc(CollisionLayer::Player);

	hurt_box->addLayerDest(CollisionLayer::Enemy, [this]() {

		if (isInvincible)
		{
			return;
		}
		hp--;
		isInvincible = true;
		});
	hurt_box->addLayerDest(CollisionLayer::EnermyBullet, [this]() {
		if (isInvincible)
		{
			return;
		}
		hp--;
		isInvincible = true;
		});

	hurtBoxSize = { size.x,size.y/2 };
	hurt_box->setSize(hurtBoxSize);


	//timer
	rollTimer.set_one_shot(true);
	rollTimer.set_wait_time(rolltime);
	rollTimer.set_on_timeout([&]() {
		isRolling = false;
		rollTimer.restart();
		/*hurt_box->setEnabled(true);*/
		
		});

	invincibleTimer.set_one_shot(true);
	invincibleTimer.set_wait_time(invincibleTime);
	invincibleTimer.set_on_timeout([&]() {
		isInvincible = false;
		invincibleTimer.restart();
		});


}

Player::~Player()
{
	ObjectManager::Instance()->RemoveObject(playerBullet);
}

void Player::Input(char* keys, char* prekeys)
{
	(void)keys;
	(void)prekeys;
	if (keys[DIK_W])
	{
		isUp = true;
	}
	else
	{
		isUp = false;
	}
	if (keys[DIK_S])
	{
		isDown = true;
	}
	else
	{
		isDown = false;
	}
	if (keys[DIK_A])
	{
		isLeft = true;
	}
	else
	{
		isLeft = false;
	}
	if (keys[DIK_D])
	{
		isRight = true;
	}
	else
	{
		isRight = false;
	}

	if (keys[DIK_SPACE])
	{
		isJumpButton = true;
	}
	else
	{
		isJumpButton = false;
	}

	if (Novice::IsTriggerMouse(1))
	{
		isRollButton = true;
	}
	else
	{
		isRollButton = false;
	}

	if(Novice::IsPressMouse(0))
	{
		isAimButton = true;
	}
	else
	{
		isAimButton = false;
	}



}

void Player::Update()
{
	Vector3 dir = { float(isRight - isLeft),float(isUp - isDown) ,0.0f };

	if (isRollButton && !isRolling)
	{
		isRolling = true;
		isAiming = false;
		//hurt_box->setEnabled(false);
		//翻滚是无敌
		if (isHaveBullet)
		{
			if (playerBullet->getState() == PlayerBullet::BulletState::Aim)
			{
				playerBullet->getStateMachine().SwitchTo("Follow");
			}
		}

	}

		if (isAimButton && !isRolling && !isAiming)
		{
			isAiming = true;
			//如果持有子弹，处理瞄准
			if (isHaveBullet)
			{
				playerBullet->getStateMachine().SwitchTo("Aim");
			}
		}
	

	if (isRolling)
	{
		rollTimer.on_update(deltaTime);
		velocity = toward * speed * 2;
	}
	else 
	{
		toward = dir.normalize();
		if (isAiming){
			velocity = toward * speed * 0.3f;
			if (!isHaveBullet && playerBullet->getIsCanBack())
			{
				//让子弹飞向玩家
				Vector2 dir_bu = { pos.x - playerBullet->GetPos().x,pos.y - playerBullet->GetPos().y };
				dir_bu = dir_bu.normalize();
				playerBullet->SetVelocity(Vector3(dir_bu.x, dir_bu.y,0.0f ) * playerBullet->GetSpeed());
			}
		}
		else
		{
			velocity = toward * speed;
		}

	}
		
	if (isAiming && !isAimButton)//松开鼠标
	{
		isAiming = false;
		if (isHaveBullet)
		{
			if (playerBullet->getIsCanShoot())
			{
				playerBullet->getStateMachine().SwitchTo("Shooted");
				isHaveBullet = false;
			}
			else
			{
				playerBullet->getStateMachine().SwitchTo("Follow");
			}
		}



	}

	if (isJumpButton && isOnGround)
	{
		//acceleration.z = jumpForce;
	}	

	//如果没有子弹，让子弹回到玩家身边
	if (!isHaveBullet && playerBullet->getIsCanPick())
	{
		//计算子弹与玩家的距离
		Vector2 dir_bu = { pos.x - playerBullet->GetPos().x,pos.y - playerBullet->GetPos().y };
		float dis = dir_bu.length();
		if (dis < size.x)
		{
			playerBullet->getStateMachine().SwitchTo("Follow");
			isHaveBullet = true;
		}

		
	}
	
	shadowSize = { (size.x / 2 + 8) * (1.0f - pos.z * 0.005f), (size.y / 2 - 5) * (1.0f - pos.z * 0.005f) };
	Charactor::Update();

	//无敌时间
	if (isInvincible)
	{

		invincibleTimer.on_update(deltaTime);

		if (curcolor == bodycolor)
		{
			curcolor = invincibleColor;
		}
		else
		{
			curcolor = bodycolor;
		}
		
	}

	if (hp <= 0)
	{
		isDead = true;
	}


}

void Player::Draw(const Camera& camera)
{
	
	Object::Draw(camera);
	//Vector2 screenleftTop = TransformFrom3D(Vector3(leftTop.x,leftTop.y,pos.z), objectMatrix,camera.heightscale);
	Vector2 screenleftTop = Transform(leftTop, objectMatrix);
	//Charactor::Draw(camera);
	Novice::DrawBox(int(screenleftTop.x), int(screenleftTop.y - pos.z * camera.heightscale), int(size.x), int(size.y), 0.0f, curcolor, kFillModeSolid);
	

#ifdef _DEBUG


		//Object::DrawDebug(camera);
		ImGui::Begin("Player");
		ImGui::Text("pos: %.2f %.2f %.2f", pos.x, pos.y,pos.z);
		ImGui::Text("toward: %.2f %.2f %.2f", toward.x, toward.y, toward.z);
		
		ImGui::Text("velocity: %.2f %.2f %.2f", velocity.x, velocity.y, velocity.z);

		ImGui::Text("isOnGround: %d", isOnGround);
		ImGui::Text("isRolling: %d", isRolling);
		ImGui::Text("isAiming: %d", isAiming);
		ImGui::Text("isHaveBullet: %d", isHaveBullet);
		ImGui::Text("hp: %d", hp);
		ImGui::Text("isInvincible: %d", isInvincible);


		//ImGui::DragFloat("height", &height, 0.1f, 0.0f, 100.0f);
		ImGui::DragFloat("gravity", &gravity, 0.1f, 0.0f, 2.0f);
		ImGui::DragFloat("jumpForce", &jumpForce, 0.1f, 0.0f, 100.0f);


		ImGui::End();
	#endif // DEBUG
}

void Player::ClearNodes()
{

}
