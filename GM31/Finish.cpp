#include "Finish.h"
#include"Title.h"
#include"polygon2D.h"
#include"Keyboard.h"
#include"manager.h"
#include "Game.h"
#include"FinishLog.h"
#include"Fade.h"
void Finish::Init()
{
	AddGameObj<FinishLog>(2);
	fade = AddGameObj<Fade>(2);
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
