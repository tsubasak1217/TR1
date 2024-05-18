#include "Scene_Title.h"

#include "Scene_Select.h"
#include "Scene_Clear.h"
#include "Scene_Game.h"
#include "Scene_Transition.h"
#include "SceneManager.h"


Scene_Title::Scene_Title() {
}

Scene_Title::~Scene_Title() {
}

void Scene_Title::Init() {
}

void Scene_Title::Update() {
	if (InputKey::trigger[DIK_RETURN]) {
		SceneManager::SetScene(new Scene_Select());
	}
}

void Scene_Title::Draw() {
#ifdef _DEBUG
	Novice::ScreenPrintf(20, 20, "scene: Title");
#endif //_DEBUG
}

void Scene_Title::Fin() {
}
