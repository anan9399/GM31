#include"Game.h"
#include"main.h"
#include"renderer.h"
#include"manager.h"
#include "GameObject.h"
#include "polygon2D.h"
#include"Field.h"
#include"Camera.h"
#include"Player.h"
#include"Enemy.h"
#include"Bullet.h"
#include"Explosion.h"
#include"Billboard.h"
#include"Cylinder.h"
#include"Box.h"

void Game::Init()
{

	AddGameObj<Camera>(0);
	AddGameObj<Field>(1)->SetPos({ 0.0f,0.0f,0.0f });


	AddGameObj<Player>(1);

	Cylinder* cylinder = AddGameObj<Cylinder>(1);
	cylinder->SetScale({ 2.0f,2.0f,2.0f });
	cylinder->SetPos({ -5.0f,0.5f,5.0f });

	Box* box = AddGameObj<Box>(1);
	box->SetScale({ 10.0f,1.0f,2.0f });
	box->SetPos({ 10.0f,0.5f,-4.0f });


	cylinder = AddGameObj<Cylinder>(1);
	cylinder->SetScale({ 2.0f,2.0f,2.0f });
	cylinder->SetPos({ -13.0f,8.0f,5.0f });

	AddGameObj<Enemy>(1)->SetPos({ -3.0f,1.0f,3.0f });
	AddGameObj<Enemy>(1)->SetPos({ 3.0f,1.0f,3.0f });
	// TODO: seperate the billboard to a new render query
	//		 need a layer for effect
	//AddGameObj<Billboard>(1)->SetPos({ 3.0f,2.0f,5.0f });

	AddGameObj<polygon2D>(2);


}

void Game::UnInit()
{
}

void Game::Update()
{
	Scene::Update();
}
