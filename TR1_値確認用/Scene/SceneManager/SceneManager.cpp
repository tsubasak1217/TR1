#include "SceneManager.h"

// static init
Scene* SceneManager::scene_ = nullptr;
bool SceneManager::isTransition_ = false;

//--------------------------------------------------------------------------------
SceneManager::SceneManager(Scene* scene) {
	Init(scene);
}

SceneManager::~SceneManager() {
}

//--------------------------------------------------------------------------------
void SceneManager::Init(Scene* scene) {
	scene_ = scene;
}

//--------------------------------------------------------------------------------
void SceneManager::Update() {
	if (isTransition_) {
		transition_->Update();
	}

	scene_->Update();
	
}

//--------------------------------------------------------------------------------
void SceneManager::Draw() {

	scene_->Draw();
	
	if (isTransition_) {
		transition_->Draw();
	}
}

//--------------------------------------------------------------------------------
void SceneManager::Fin() {
}


void SceneManager::SetScene(Scene* scene) {
	delete scene_;
	scene_ = scene;
}
