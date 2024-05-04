#pragma once
#include "Scene.h"
#include "Container.h"

class Scene_Game final : public Scene {

public:

	Scene_Game();
	~Scene_Game();

	void Init() override;
	void Update()override;
	void Draw()override;
	void Fin()override;

private:
	bool isDraw_;
	int frameCount_;
	int getFrame_;
	std::vector<Container> container_;

	void Exponentiation(Container* container);
};