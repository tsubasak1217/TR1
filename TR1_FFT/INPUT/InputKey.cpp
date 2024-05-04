#include "InputKey.h"
#include <Novice.h>

char InputKey::keys[kMaxKey_] = { 0 };
char InputKey::preKeys[kMaxKey_] = { 0 };
bool InputKey::trigger[kMaxKey_] = { false };
bool InputKey::release[kMaxKey_] = { false };
Vector2<int> InputKey::mousePos_ = { 0,0 };
int InputKey::mousePress_[2] = { 0 };
int InputKey::preMousePress_[2] = { 0 };
int InputKey::mouseTrigger_[2] = { 0 };
int InputKey::mouseRelease_[2] = { 0 };

void InputKey::Update() {

	Novice::GetMousePosition(&mousePos_.x, &mousePos_.y);
	for (int i = 0; i < 2; i++) {
		preMousePress_[i] = mousePress_[i];
		mousePress_[i] = Novice::IsPressMouse(i);
		mouseTrigger_[i] = Novice::IsTriggerMouse(i);
		mouseRelease_[i] = (preMousePress_[i] - mousePress_[i] == 1);
	}

	for (int i = 0; i < kMaxKey_; i++) {
		trigger[i] = !preKeys[i] && keys[i];
		release[i] = preKeys[i] && !keys[i];
	}
}
