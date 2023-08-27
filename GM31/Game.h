#pragma once
#include "Scene.h"

class Game : public Scene
{
public:
	void Init()override;
	void UnInit()override;
	void Update()override;
private:
	int* score;
	class Audio* m_bgm;
	class Fade* fade;
};