#pragma once
#include "Scene.h"

class Scene_Title final : public Scene {

public:

	Scene_Title();
	~Scene_Title();

	void Init() override;
	void Update()override;
	void Draw()override;
	void Fin()override;
};

