#pragma once
#include "Scene.h"

class Game : public Scene
{
public:
	void Init()override;
	void UnInit()override;
	void Update()override;
private:
	bool m_finished = false;
	int m_time;
	int m_score;
	class Audio* m_bgm;
	class Fade* fade;
};