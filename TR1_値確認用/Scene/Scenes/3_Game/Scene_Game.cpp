#include "Scene_Game.h"

#include "Scene_Title.h"
#include "Scene_Select.h"
#include "Scene_Clear.h"
#include "Scene_Transition.h"
#include "SceneManager.h"

Scene_Game::Scene_Game() {
	Init();
}

Scene_Game::~Scene_Game() {
}

void Scene_Game::Init() {
	complex_.resize(8);
}

void Scene_Game::Update() {
	if (InputKey::trigger[DIK_RETURN]) {
		SceneManager::SetScene(new Scene_Clear());
	}
	
	for(int i = 0; i < complex_.size(); i++){
		Novice::ScreenPrintf(20, 60 + 20 * i, "{%3f,%3f}", complex_[i].real(), complex_[i].imag());
	}
}

void Scene_Game::Draw() {
#ifdef _DEBUG
	Novice::ScreenPrintf(20, 20, "scene: Game");
#endif //_DEBUG
}

void Scene_Game::Fin() {
}
