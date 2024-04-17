#pragma once
#include <map>
#include <string>

class MyTextureManager {

public:
	MyTextureManager();
	~MyTextureManager();

	void Init();
	void Fin();

public:
	static std::map <std::string,int> texture_;
};

