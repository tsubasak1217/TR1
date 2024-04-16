#include "InputKey.h"

char InputKey::keys[kMaxKey_] = { 0 };
char InputKey::preKeys[kMaxKey_] = { 0 };
bool InputKey::trigger[kMaxKey_] = { false };
bool InputKey::release[kMaxKey_] = { false };

void InputKey::Update() {

	for (int i = 0; i < kMaxKey_; i++) {
		trigger[i] = !preKeys[i] && keys[i];
		release[i] = preKeys[i] && !keys[i];
	}
}
