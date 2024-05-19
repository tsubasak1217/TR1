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
	std::vector<double>data_;
	std::vector<std::complex<double>>complex_;
	std::vector<std::complex<double>>FFTdata_;
	std::vector<std::complex<double>>DFTdata_;
	std::vector<std::complex<double>>IFFTdata_;
	std::vector<std::complex<double>>IDFTdata_;
	int step;

private:
	std::vector<double> Exponentiation(std::vector<double> data);
	void Butterfly(std::vector<std::complex<double>>* data, bool inverse);
	std::vector<std::complex<double>> FFT(const std::vector<double>& data);
	std::vector<std::complex<double>> DFT(const std::vector<double>& data);
	std::vector<std::complex<double>> IDFT(const std::vector<std::complex<double>>& FFTdata);
	std::vector<std::complex<double>> IFFT(const std::vector<std::complex<double>>& FFTdata);
};