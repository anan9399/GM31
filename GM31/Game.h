#pragma once
#include "Scene.h"

class Game : public Scene
{
public:
	void Init()override;
	void UnInit()override;
	void Update()override;
	static int m_time;
private:
	bool m_finished = false;
	bool m_win = false;
	
	int m_score;
	class Audio* m_bgm;
	class Fade* fade;
};