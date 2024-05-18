#include "Scene_Clear.h"

#include "Scene_Title.h"
#include "Scene_Select.h"
#include "Scene_Game.h"
#include "Scene_Transition.h"
#include "SceneManager.h"

Scene_Clear::Scene_Clear() {
}

Scene_Clear::~Scene_Clear() {
}

void Scene_Clear::Init() {
}

void Scene_Clear::Update() {
	if (InputKey::trigger[DIK_RETURN]) {
		SceneManager::SetScene(new Scene_Title());
	}
}

void Scene_Clear::Draw() {
#ifdef _DEBUG
	Novice::ScreenPrintf(20, 20, "scene: Clear");
#endif //_DEBUG
}

void Scene_Clear::Fin() {
}
