#pragma once
#include "Scene.h"
#include"Game.h"

class Failure : public Scene
{
	friend class Game;
public:
	void Init() override;
	void UnInit()override;
	void Update()override;
	class Fade* fade;
};
