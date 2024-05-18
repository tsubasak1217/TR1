#include "Scene_Select.h"

#include "Scene_Title.h"
#include "Scene_Clear.h"
#include "Scene_Game.h"
#include "Scene_Transition.h"
#include "SceneManager.h"

Scene_Select::Scene_Select() {
}

Scene_Select::~Scene_Select() {
}

void Scene_Select::Init() {
}

void Scene_Select::Update() {
	if (InputKey::trigger[DIK_RETURN]) {
		SceneManager::SetScene(new Scene_Game());
	}
}

void Scene_Select::Draw() {
#ifdef _DEBUG
	Novice::ScreenPrintf(20, 20, "scene: Select");
#endif //_DEBUG
}

void Scene_Select::Fin() {
}
