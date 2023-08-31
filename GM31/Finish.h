#pragma once
#include "Scene.h"
#include"Game.h"
class Finish : public Scene
{
	friend class Game;
public:
	void Init() override;
	void UnInit()override;
	void Update()override;
	class Fade* fade;
};
