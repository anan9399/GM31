#include "Finish.h"
#include"Title.h"
#include"polygon2D.h"
#include"Keyboard.h"
#include"manager.h"
#include "Game.h"
#include"FinishLog.h"
#include"Fade.h"
#include"Score.h"

void Finish::Init()
{
	AddGameObj<FinishLog>(2);
	fade = AddGameObj<Fade>(2);

	auto score = AddGameObj<Score>(2);
	score->AddCount(Game::m_time);
	score->SetScale({ 2.5f,2.5f,1.0f });
	score->SetPos({480.0f,400.0f,0.0f});

}

void Finish::UnInit()
{
}

void Finish::Update()
{
	Scene::Update();
	if (Keyboard::GetKeyTrigger(VK_RETURN)) {
		fade->FadeOut();
	}
	if (fade->GetFadeFinished()) {
		Manager::SetScene<Title>();
	}
}
