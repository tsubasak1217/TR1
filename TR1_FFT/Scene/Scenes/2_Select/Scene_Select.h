#pragma once
#include "Scene.h"

class Scene_Select final : public Scene {

public:

	Scene_Select();
	~Scene_Select();

	void Init() override;
	void Update()override;
	void Draw()override;
	void Fin()override;
};

