#pragma once
#include "Scene.h"
#include "MyFunc.h"

class Scene_Game final : public Scene {

public:

	Scene_Game();
	~Scene_Game();

	void Init() override;
	void Update()override;
	void Draw()override;
	void Fin()override;

private:
	std::vector<std::complex<float>>complex_;
};