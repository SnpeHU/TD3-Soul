#include <Novice.h>
#include <Manager/SceneManager.h>
#include <Manager/CharactorManager.h>
#include <Manager/ObjectManager.h>
#include "Camera.h"
//debug
#ifdef _DEBUG
#include<imgui.h>
#endif // DEBUG


const char kWindowTitle[] = "GC1A_05_コウ_ホウケイ_タイトル";

 float windowWidth = 1280;
float windowHeight = 720;

Camera m_camera(Vector2(0.0f, 0.0f));

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	
	

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
		
		SceneManager::Instance()->onInput(keys, preKeys);
		SceneManager::Instance()->Update();
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		SceneManager::Instance()->Draw(m_camera);


#ifdef _DEBUG
		ImGui::Begin("BasicInfo");
		ImGui::Text("SceneName:%s",(SceneManager::Instance()->getCurrentScene()->s_name).c_str());
		ImGui::End();

		ImGui::Begin("Camera");
		ImGui::Text("pos: %.2f %.2f", m_camera.GetPos().x, m_camera.GetPos().y);
		ImGui::Text("scale: %.2f", m_camera.GetScale());
		ImGui::End();
#endif


		

		

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
