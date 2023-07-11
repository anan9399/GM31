#pragma once
#include "Scene.h"

class Finish : public Scene
{
public:
	void Init() override;
	void UnInit()override;
	void Update()override;
	class Fade* fade;
};
