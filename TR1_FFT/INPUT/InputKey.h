#pragma once
class InputKey {
public:
	static const int kMaxKey_ = 256;
	static char keys[kMaxKey_];
	static char preKeys[kMaxKey_];

	static bool trigger[kMaxKey_];
	static bool release[kMaxKey_];

	static void Update();
};

