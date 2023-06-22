#include "Title.h"
#include"polygon2D.h"
#include"Keyboard.h"
#include"manager.h"
#include "Game.h"
#include"TitleLog.h"
void Title::Init()
{
	AddGameObj<TitleLog>(2);
}

void Title::UnInit()
{
}

void Title::Update()
{
	Scene::Update();
	if (Keyboard::GetKeyTrigger(VK_RETURN)) {
		Manager::SetScene<Game>();
	}
}
