#include "PlayerBullet.h"
#include "Manager/CharactorManager.h"
#include "State/PlayerBulletState.h"
#include "Emitter/BlockEmiiter.h"	
#ifdef _DEBUG
#include<imgui.h>
#endif // DEBUG
PlayerBullet::PlayerBullet(Vector3 pos)
{
	this->pos = pos;
	toward = { 1.0f,0.0f,0.0f };
	size = { 10.0f,10.0f };
	speed = 4.0f;
	color = 0x717170FF;

	isDeBug = true;
	name = "PlayerBullet";
	//collisionbox
	hurt_box = CollisionManager::Instance()->CreatCollisionBox(this);
	hurt_box->setLayerSrc(CollisionLayer::PlayerBullet);

	hurtBoxSize = { size.x * 2 - 3,size.y *2 - 3 };
	hurt_box->setSize(hurtBoxSize);
	hurt_box->setEnabled(false);

	//stateMachine
	stateMachine.RegisterState("Follow", new FollowState(this));
	stateMachine.RegisterState("Aim", new AimState(this));
	stateMachine.RegisterState("Shooted", new ShootedState(this));
	stateMachine.SetEntry("Follow");

	//tailEmitter = std::make_unique<BlockEmitter>(pos, 0.02f, Vector2(5.0f, 5.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 1.0f, 0.0f, 0xFFFFFFFF);
	tailEmitter = new BlockEmitter(pos, 0.03f, Vector2(15.0f, 15.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 0.5f, 0.0f, 0x717170FF);
	//tailEmitter = new BlockEmitter(Vector3(0.0f, 30.0f, 0.0f), 0.5f);
	//tailEmitter->SetEnable(true);
}

PlayerBullet::~PlayerBullet()
{
	delete tailEmitter;
	tailEmitter = nullptr;
}

void PlayerBullet::Update()
{
	
	shadowSize = { (size.x + size.x/4) * (1.0f - pos.z * 0.003f), (size.y - size.y/4) * (1.0f - pos.z * 0.003f) };//影子大小更新
	Vector2 screenPos;
	Vector2 mousePos;
	int mouseX, mouseY;
	Vector2 dir;

	stateMachine.onUpdate();

	switch (curstate)
	{
	case PlayerBullet::BulletState::FollowPlayer:
		//围绕玩家旋转
		rotateCenter = CharactorManager::Instance()->GetPlayer()->GetPos();
		rotateAngle += 0.1f; 
		pos.x = rotateCenter.x + rotateRadius * cos(rotateAngle);
		pos.y = rotateCenter.y + rotateRadius * sin(rotateAngle);
		pos.z = 20.0f;

		if (rotateAngle > 720.0f)
		{
			rotateAngle = 0.0f;
		}

		break;
	case PlayerBullet::BulletState::Aim:
		//玩家瞄准，子弹上下抖动
		rotateCenter = CharactorManager::Instance()->GetPlayer()->GetPos();
		pos.x = rotateCenter.x + rotateRadius * cos(rotateAngle);
		pos.y = rotateCenter.y + rotateRadius * sin(rotateAngle);
		shakePosZ = (-50 + rand() % 100) / 50.0f * 2.0f;

		screenPos = Transform(Vector2(0.0f, 0.0f), objectMatrix);//用于计算子弹发射位置与鼠标位置的角度
		Novice::GetMousePosition(&mouseX, &mouseY);
		mousePos.x = static_cast<float>(mouseX);
		mousePos.y = static_cast<float>(mouseY);
		dir = (mousePos - screenPos).normalize();
		dir.y *= -1.0f;//坐标系转换
		toward.x = dir.x;
		toward.y = dir.y;
		
		break;
	case PlayerBullet::BulletState::Shooted:
		//子弹发射,向鼠标方向发射
		acceleration = velocity * (-kAirResistance);
		velocity += acceleration;
		if (!isCanBack)
		{
			if (velocity.length() < 0.1f)
			{
				velocity = { 0.0f,0.0f,0.0f };
				isCanBack = true;
			}
		}


		pos += velocity;

		break;
	default:
		break;
	}
	
	tailEmitter->Update();
	tailEmitter->SetPos(pos);


	//当速度大于5时，可以造成伤害，否则不造成伤害
	if (velocity.length() > 5.0f)
	{
		isCanDamage = true;
		if(!tailEmitter->GetEnable())
		{
			//tailEmitter->SetEnable(true);
		}
	}
	else
	{
		isCanDamage = false;
		if (tailEmitter->GetEnable())
		{
			//tailEmitter->SetEnable(false);
		}
	}

	//collisionbox

		if (hurt_box)
		{
			hurt_box->setPos(get_logic_center());
		}
}

void PlayerBullet::Draw(const Camera& camera)
{
	Object::Draw(camera);
	Vector2 screenDrawPos = Transform(Vector2(0.0f, size.y), objectMatrix);
	Novice::DrawEllipse(int(screenDrawPos.x), int(screenDrawPos.y - (pos.z + shakePosZ) * camera.heightscale), int(size.x), int(size.y), 0.0f, color, kFillModeSolid);

#ifdef _DEBUG


	//Object::DrawDebug(camera);
	ImGui::Begin("PlayerBullet");
	ImGui::Text("pos: %.2f %.2f %.2f", pos.x, pos.y, pos.z);
	ImGui::Text("toward: %.2f %.2f %.2f", toward.x, toward.y, toward.z);
	ImGui::Text("speed: %.2f", speed);
	ImGui::Text("velocity: %.2f %.2f %.2f", velocity.x, velocity.y, velocity.z);
	ImGui::Text("currentState: %s", stateMachine.GetCurrentState().c_str());

	ImGui::Text("isCanBack: %d", isCanBack);
	ImGui::Text("isCanPick: %d", isCanPick);
	ImGui::Text("isRebound: %d", isRebound);
	ImGui::Text("isCanShoot: %d", isCanShoot);
	ImGui::Text("isCanDamage: %d", isCanDamage);


	

	ImGui::End();
#endif // DEBUG
}

void PlayerBullet::switchState(BulletState state)
{

	curstate = state;
}
