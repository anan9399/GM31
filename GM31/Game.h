#pragma once
#include "Scene.h"

class Game : public Scene
{
public:
	void Init()override;
	void Update()override;
private:
	int* score;
	class Audio* m_bgm;
};