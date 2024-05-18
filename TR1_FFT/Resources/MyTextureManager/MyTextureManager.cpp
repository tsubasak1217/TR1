#include "MyTextureManager.h"
#include <Novice.h>

std::map <std::string, int>MyTextureManager::texture_;

MyTextureManager::MyTextureManager() {}

MyTextureManager::~MyTextureManager() {}

void MyTextureManager::Init() {

	std::string curDir = "./Resources/MyTextureManager/Images/";

	texture_["white1x1"] = Novice::LoadTexture("white1x1.png");
	texture_["ellipseLine"] = Novice::LoadTexture("./Resources/MyTextureManager/Images/ellipseLine.png");
}

void MyTextureManager::Fin() {
}
