#include "Scene_Game.h"

#include "Scene_Title.h"
#include "Scene_Select.h"
#include "Scene_Clear.h"
#include "Scene_Transition.h"
#include "SceneManager.h"

Scene_Game::Scene_Game() {
}

Scene_Game::~Scene_Game() {
}

void Scene_Game::Init() {
}

void Scene_Game::Update() {
	if (InputKey::trigger[DIK_RETURN]) {
		SceneManager::SetScene(new Scene_Clear());
	}
}

void Scene_Game::Draw() {
#ifdef _DEBUG
	Novice::ScreenPrintf(20, 20, "scene: Game");
#endif //_DEBUG
}

void Scene_Game::Fin() {
}
