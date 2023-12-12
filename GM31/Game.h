#pragma once
#include "Scene.h"

class Game : public Scene
{
public:
	static void Load();
	void Unload();
	void Init()override;
	void UnInit()override;
	void Update()override;
	static bool GetLoadFinish() { return m_LoadFinish; };

	static int m_time;
private:
	bool m_finished = false;
	bool m_win = false;
	static bool m_LoadFinish;
	int m_score;
	class Audio* m_bgm;
	class Fade* fade;
};