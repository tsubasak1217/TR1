#pragma once
#include <Novice.h>

class SceneManager;

class GameManager {

public:
	GameManager(SceneManager* sceneManager);
	~GameManager();

	static void Init(SceneManager* sceneManager);
	static void Update();
	static void Draw();
	static void Run();
	static void Finalize();

private:
	static SceneManager* sceneManager_;
};

