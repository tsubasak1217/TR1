#pragma once
#include "Scene.h"

class Scene_Clear final : public Scene {

public:

	Scene_Clear();
	~Scene_Clear();

	void Init() override;
	void Update()override;
	void Draw()override;
	void Fin()override;
};