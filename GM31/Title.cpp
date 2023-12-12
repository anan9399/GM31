#include "Title.h"
#include"polygon2D.h"
#include"Keyboard.h"
#include"manager.h"
#include "Game.h"
#include"TitleLog.h"
#include"Fade.h"
#include"LoadingLog.h"
#include"LoadScene.h"
void Title::Init()
{
	m_se = AddGameObj<TitleLog>(2)->AddComponent<Audio>();
	m_se->Load("asset\\audio\\solid.wav");
	fade = AddGameObj<Fade>(2);
}

void Title::UnInit()
{
}

void Title::Update()
{
	Scene::Update();
	if (Keyboard::GetKeyTrigger(VK_RETURN)) {
		m_se->Play();
		fade->FadeOut();
	}
	if (fade->GetFadeFinished()) {
		//AddGameObj<LoadingLog>(2);
		//Draw();
		Manager::SetScene<LoadScene>();
	}
}
