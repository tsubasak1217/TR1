#pragma once
#include <vector>
#include "VectorN.h"
#include "MyFunc.h"

struct Container {
	std::vector<float>positionX_;
	std::vector<float>positionY_;
	std::vector<Vec2>pos_[2];
	std::vector<Vec2>swapPos_[2];

	std::vector<FFTResult> resultX_;
	std::vector<FFTResult> resultY_;

	void Draw(int getFrame);
};

