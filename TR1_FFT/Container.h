#pragma once
#include <vector>
#include "VectorN.h"

struct Container {
	std::vector<Vec2>positions_;
	void Draw(int getFrame);
};

