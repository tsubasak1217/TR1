#pragma once
#include "Scene.h"



class SceneManager {

public:
	SceneManager(Scene* scene_);
	~SceneManager();

	void Init(Scene* scene);
	void Update();
	void Draw();
	void Fin();

private:
	static bool isTransition_;
	Scene* transition_;
	static Scene* scene_;

public:
	static void SetScene(Scene* scene);

};

