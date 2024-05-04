#pragma once
#include "VectorN.h"
class InputKey {
public:
	static const int kMaxKey_ = 256;
	static char keys[kMaxKey_];
	static char preKeys[kMaxKey_];

	static bool trigger[kMaxKey_];
	static bool release[kMaxKey_];

	static Vector2<int>mousePos_;
	static int mousePress_[2];
	static int preMousePress_[2];
	static int mouseTrigger_[2];
	static int mouseRelease_[2];

	static void Update();
};

