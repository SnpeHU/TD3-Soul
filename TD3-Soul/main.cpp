#include <Novice.h>
#include <Manager/SceneManager.h>
#include <Manager/CharactorManager.h>
#include <Manager/ObjectManager.h>
#include "Camera.h"
#include "Tool/read_csv.h"
//debug
#ifdef _DEBUG
#include<imgui.h>
#endif // DEBUG


const char kWindowTitle[] = "GC1A_04_GEO SOULS";

float windowWidth = 1280;
float windowHeight = 720;



Camera m_camera(Vector2(0.0f, 0.0f));


//aim
int aimPosX;
int aimPosY;
int aimLength = 8;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	//int StartImg = 0;//Novice::LoadTexture("./rs/start.png");


	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	int guidePosX = 1060;
	int guidePosY = 620;
	
	int guideImg = Novice::LoadTexture("./rs/guide.png");


	// シーンマネージャーの初期化
	SceneManager::Instance()->Init();
	

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		Novice::SetMouseCursorVisibility(0);
		Novice::GetMousePosition(&aimPosX, &aimPosY);

		SceneManager::Instance()->onInput(keys, preKeys);
		SceneManager::Instance()->Update();
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		SceneManager::Instance()->Draw(m_camera);
		Novice::DrawBox(aimPosX - aimLength, aimPosY, aimLength, 3, 0.0f, 0x00BFFFff, kFillModeSolid);
		Novice::DrawBox(aimPosX + aimLength, aimPosY, aimLength, 3, 0.0f, 0x00BFFFff, kFillModeSolid);
		Novice::DrawBox(aimPosX + 2, aimPosY + aimLength - 2, 3, aimLength, 0.0f, 0x00BFFFff, kFillModeSolid);
		Novice::DrawBox(aimPosX + 2, aimPosY - aimLength - 2, 3, aimLength, 0.0f, 0x00BFFFff, kFillModeSolid);

#ifdef _DEBUG
		ImGui::Begin("BasicInfo");
		ImGui::Text("SceneName:%s",(SceneManager::Instance()->getCurrentScene()->s_name).c_str());
		ImGui::End();

		ImGui::Begin("Camera");
		ImGui::Text("pos: %.2f %.2f", m_camera.GetPos().x, m_camera.GetPos().y);
		ImGui::Text("scale: %.2f", m_camera.GetScale());
		ImGui::End();
#endif


		//guide	表示する
		Novice::DrawSprite(guidePosX, guidePosY, guideImg,1.0f ,1.0f, 0.0f, WHITE);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	SceneManager::Instance()->DestroyInstance();
	CharactorManager::Instance()->DestroyInstance();
	ObjectManager::Instance()->DestroyInstance();
	Novice::Finalize();
	return 0;
}
