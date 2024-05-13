#pragma once
#include "Scene.h"
#include "Container.h"
#include "VectorN.h"
#include <vector>
#include <complex>

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

	std::vector<float> Exponentiation(std::vector<float> data);
	void Butterfly(std::vector<std::complex<float>>* data);
	std::vector<std::complex<float>> FFT(const std::vector<float>& data);
};