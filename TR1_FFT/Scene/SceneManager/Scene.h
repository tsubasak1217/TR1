﻿#pragma once
#include <Novice.h>
#include "Environment.h"
#include "InputKey.h"

class Scene {

public:

	Scene();
	virtual ~Scene();

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Fin();

};

