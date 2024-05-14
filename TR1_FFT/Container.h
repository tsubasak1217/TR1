#pragma once
#include <vector>
#include "VectorN.h"
#include "MyFunc.h"

struct Container {
	std::vector<float>positionX_;
	std::vector<float>positionY_;

	std::vector<FFTResult> resultX_;
	std::vector<FFTResult> resultY_;
	float maxLevel_;
	bool isDrawFourier_;

	void Draw(int getFrame);
};

