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
	int drawCount_;
	int frameCount_;
	int getFrame_;
	std::vector<Container> container_;
	std::vector<std::complex<float>> FFT_[2];
	std::vector<std::complex<float>> DFT_[2];
	std::vector<std::complex<float>> IDFT_[2];
	std::vector<std::complex<float>> IFFT_[2];

	bool isDrawFourier_;
	Vec2 fourierCenter_[2];
	Vec2 fourierPoint_[2];

private:
	std::vector<float> Exponentiation(std::vector<float> data);
	std::vector<Vec2> Exponentiation(std::vector<Vec2> data);
	void Butterfly(std::vector<std::complex<float>>* data,bool inverse);
	std::vector<std::complex<float>> FFT(const std::vector<float>& data);
	std::vector<std::complex<float>> FFT(const std::vector<Vec2>& data);
	std::vector<std::complex<float>> DFT(const std::vector<float>& data);
	std::vector<std::complex<float>> DFT(const std::vector<Vec2>& data);
	std::vector<std::complex<float>> IDFT(const std::vector<std::complex<float>>& FFTdata);
	std::complex<float> IDFT(const std::vector<std::complex<float>>& FFTdata,float time);
	std::vector<std::complex<float>> IFFT(const std::vector<std::complex<float>>& FFTdata);

	std::vector<FFTResult> TransformFFT(const std::vector<std::complex<float>>& data);
	std::vector<FFTResult> SortFFT(const std::vector<FFTResult>& data);
};