#include "Scene_Game.h"
#include "Scene_Title.h"
#include "Scene_Select.h"
#include "Scene_Clear.h"
#include "Scene_Transition.h"
#include "SceneManager.h"
#include "Environment.h"
#include "MyFunc.h"
#include "MyTextureManager.h"


Scene_Game::Scene_Game() {
	Init();
}

Scene_Game::~Scene_Game() {
}

void Scene_Game::Init() {
	isDraw_ = false;
	frameCount_ = 0;
	getFrame_ = 4;
	container_.clear();
}

void Scene_Game::Update() {
	if (InputKey::trigger[DIK_RETURN]) {
		//SceneManager::SetScene(new Scene_Clear());
		container_.push_back(Container());
	}

	// 描画フラグをオンにする
	if (InputKey::mousePos_.x >= windowLT.x && InputKey::mousePos_.x <= windowRB.x) {
		if (InputKey::mousePos_.y >= windowLT.y && InputKey::mousePos_.y <= windowRB.y) {
			if (InputKey::mouseTrigger_[0]) {
				isDraw_ = true;
				container_.push_back(Container());
			}
		}
	}

	// 描画フラグが立っているときの処理
	if (isDraw_) {

		frameCount_++;

		// マウスが離されたら描画終了
		if (InputKey::mouseRelease_[0]) {
			isDraw_ = false;
			frameCount_ = 0;
		}

		// getFrameのフレームごとに座標を取得してコンテナに入れる
		if (frameCount_ % getFrame_ == 0) {
			container_.back().positions_.push_back({
				float(InputKey::mousePos_.x),
				float(InputKey::mousePos_.y)
				}
			);
		}
	}
}

void Scene_Game::Draw() {

	MyFunc::DrawQuad(
		windowCenter,
		canvasSize,
		0, 0,
		1, 1,
		1.0f, 1.0f,
		"white1x1",
		0.0f,
		0xffffffff
	);

	if (container_.size() > 0) {
		container_.back().Draw(getFrame_);
	}

#ifdef _DEBUG
	Novice::ScreenPrintf(20, 20, "scene: Game");
	Novice::ScreenPrintf(20, 40, "container size: %d",container_.size());
	if (container_.size() > 0) {
		Novice::ScreenPrintf(20, 60, "points: %d", container_.back().positions_.size());
	}
#endif //_DEBUG
}

void Scene_Game::Fin() {
}

void Scene_Game::Exponentiation(Container* container) {

	assert(container->positions_.size() >= 2);
	
	// iをcontainerのデータ数以上で一番近い2のべき乗の数にする
	size_t i = 2;
	for (i = 2; i < container->positions_.size(); i *= 2) {}
	
	// iとcontainerのデータ数の差を求める
	i = i - container->positions_.size();

	// データ数を2のべき乗個にするため、差の個数分、0で埋める
	for (int j = 0; j < i; j++) {
		container->positions_.push_back({0.0f,0.0f});
	}
}
