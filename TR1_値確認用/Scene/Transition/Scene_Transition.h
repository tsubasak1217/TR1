#pragma once
#include "Scene.h"

class Scene_Transition final : public Scene {

public:

	Scene_Transition();
	~Scene_Transition();

	void Init() override;
	void Update()override;
	void Draw()override;
	void Fin()override;

};

