#include "Failure.h"
#include"Title.h"
#include"polygon2D.h"
#include"Keyboard.h"
#include"manager.h"
#include "Game.h"
#include"FailureLog.h"
#include"Fade.h"
#include"Score.h"

void Failure::Init()
{
	AddGameObj<FailureLog>(2);
	fade = AddGameObj<Fade>(2);
}

void Failure::UnInit()
{
}

void Failure::Update()
{
	Scene::Update();
	if (Keyboard::GetKeyTrigger(VK_RETURN)) {
		fade->FadeOut();
	}
	if (fade->GetFadeFinished()) {
		Manager::SetScene<Title>();
	}
}
