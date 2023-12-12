#include "LoadScene.h"
#include "Title.h"
#include"polygon2D.h"
#include"Keyboard.h"
#include"manager.h"
#include "Game.h"
#include"TitleLog.h"
#include"Fade.h"
#include"LoadingLog.h"
#include<thread>
void LoadScene::Init()
{
	AddGameObj<LoadingLog>(2);
	
	std::thread th(&Game::Load);
	th.detach();
}

void LoadScene::UnInit()
{
}

void LoadScene::Update()
{
	Scene::Update();
	if (Game::GetLoadFinish()) {
		Manager::SetScene<Game>();
	}
}
