#include "GameManager.h"
#include "SceneManager.h"
#include "Environment.h"
#include "InputKey.h"
#include "SceneManager.h"
#include "Scene_Title.h"
#include "Scene_Select.h"
#include "Scene_Clear.h"
#include "Scene_Game.h"
#include "Scene_Transition.h"

SceneManager* GameManager::sceneManager_ = nullptr;

//--------------------------------------------------------------------------------
GameManager::GameManager(SceneManager* sceneManager) {
	Init(sceneManager);
}

GameManager::~GameManager() {
}

//--------------------------------------------------------------------------------
void GameManager::Init(SceneManager* sceneManager) {
	sceneManager_ = sceneManager;
}

//--------------------------------------------------------------------------------
void GameManager::Update() {
	sceneManager_->Update();
}

//--------------------------------------------------------------------------------
void GameManager::Draw() {
	sceneManager_->Draw();
}

//--------------------------------------------------------------------------------
void GameManager::Finalize() {

}

//--------------------------------------------------------------------------------
void GameManager::Run() {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowSizeX, kWindowSizeY);

	// ゲームマネージャーのインスタンス作成
	GameManager gameManager(new SceneManager(new Scene_Game));

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();
		// キー入力を受け取る
		memcpy(InputKey::preKeys, InputKey::keys, 256);
		Novice::GetHitKeyStateAll(InputKey::keys);

		InputKey::Update();// 自分用にトリガーやリリースを取得するクラス

		// ゲームマネージャー自身の処理
		Update();
		Draw();


		// フレームの終了
		Novice::EndFrame();
	}

	// ライブラリの終了
	Finalize();
	Novice::Finalize();
}

