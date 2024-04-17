#include "Scene_Game.h"
#include "Scene_Title.h"
#include "Scene_Select.h"
#include "Scene_Clear.h"
#include "Scene_Transition.h"
#include "SceneManager.h"

#include "MyFunc.h"
#include "MyTextureManager.h"

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

	Vec2 windowCenter = { float(kWindowSizeX) * 0.5f, float(kWindowSizeY) * 0.5f };
	Vec2 canvasSize;
	canvasSize.y = float(kWindowSizeY) * 0.8f;
	canvasSize.x = canvasSize.y;

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


#ifdef _DEBUG
	Novice::ScreenPrintf(20, 20, "scene: Game");
#endif //_DEBUG
}

void Scene_Game::Fin() {
}
