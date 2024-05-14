#pragma once
#include "Scene.h"
#include "Container.h"
#include "VectorN.h"
#include <vector>
#include <complex>
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
	bool isDraw_;
	int frameCount_;
	int getFrame_;
	std::vector<Container> container_;
	std::vector<std::complex<float>> FFTX_;
	std::vector<std::complex<float>> FFTY_;
	std::vector<FFTResult> resultX_;
	std::vector<FFTResult> resultY_;
	float nyquist_;

	bool isDrawFourier_;
	Vec2 fourierPoint_;

private:
	std::vector<float> Exponentiation(std::vector<float> data);
	void Butterfly(std::vector<std::complex<float>>* data);
	std::vector<std::complex<float>> FFT(const std::vector<float>& data);

	std::vector<FFTResult> TransformFFT(const std::vector<std::complex<float>>& data,float nyquist,bool XorY);
	std::vector<FFTResult> SortFFT(const std::vector<FFTResult>& data);
};