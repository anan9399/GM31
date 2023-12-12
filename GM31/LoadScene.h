#pragma once
#include "Scene.h"

class LoadScene : public Scene
{
public:
	void Init() override;
	void UnInit()override;
	void Update()override;
private:
	class Audio* m_se;
	class Fade* fade;
};

