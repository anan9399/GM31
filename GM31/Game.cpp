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
#include"Keyboard.h"
#include"Over.h"
#include"Score.h"
#include"Finish.h"
#include"audio.h"
#include<random>
#include"Sky.h"
#include"Fade.h"
#include"SuperBullet.h"
#include"Shadow.h"
#include"EnemyCoward.h"
std::mt19937 rng({ std::random_device{}() });
std::uniform_int_distribution<int> xdist(-40.0f, 40.0f);
std::uniform_int_distribution<int> ydist(0.0f, 2.0f);
std::uniform_int_distribution<int> zdist(-40.0f, 40.0f);

void Game::Init()
{


	Bullet::Load();
	SuperBullet::Load();
	Enemy::Load();

	AddGameObj<Camera>(0);
	AddGameObj<Field>(1)->SetPos({ 0.0f,0.0f,0.0f });
	AddGameObj<Sky>(1);


	

	
	Billboard* b = AddGameObj<Billboard>(1);
	b->SetScale({ 2.0f,2.0f,2.0f });
	b->SetPos({ -13.0f,5.0f,4.0f });

	Box* box = AddGameObj<Box>(1);
	box->SetScale({ 10.0f,1.0f,2.0f });
	box->SetPos({ 10.0f,0.5f,-4.0f });


	Cylinder* cylinder = AddGameObj<Cylinder>(1);
	cylinder->SetScale({ 2.0f,2.0f,2.0f });
	cylinder->SetPos({ -13.0f,3.0f,4.0f });

	for (int i = 0; i < 20; i++) {
		box = AddGameObj<Box>(1);
		box->SetScale({ 2.0f,1.0f,2.0f });
		box->SetPos({ xdist(rng) + 1.0f,0.5f,zdist(rng)+1.0f });
	}

	//AddGameObj<Shadow>(1);
	AddGameObj<Player>(1);



	//AddGameObj<EnemyCoward>(1)->SetPos({ 10.0f, 0.0f, 10.0f });

	auto enemy2 = AddGameObj<Enemy>(1);
	enemy2->SetPos({-10.0f,1.5f,-8.0f});
	std::vector<D3DXVECTOR3> waypoints = { 
		{-10.0f,1.5f,-8.0f},
		{-20.0f,1.5f,-8.0f},
		{-20.0f,1.5f,-18.0f},
		{-10.0f,1.5f,-18.0f},
	};
	enemy2->SetWayPoints(waypoints);


	enemy2 = AddGameObj<Enemy>(1);
	enemy2->SetPos({ 10.0f,1.0f,-8.0f });
	waypoints = { 
		{ 10.0f,1.0f,-8.0f},
		{ 20.0f,1.0f,-8.0f},
		{ 20.0f,1.0f,-18.0f},
		{ 10.0f,1.0f,-18.0f}, 
	};
	enemy2->SetWayPoints(waypoints);


	enemy2 = AddGameObj<EnemyCoward>(1);
	enemy2->SetPos({ 10.0f,1.0f,8.0f });
	waypoints = {
		{ 10.0f,1.0f,8.0f},
		{ 20.0f,1.0f,8.0f},
		{ 20.0f,1.0f,18.0f},
		{ 10.0f,1.0f,18.0f},
	};
	enemy2->SetWayPoints(waypoints);


	// TODO: seperate the billboard to a new render query
	//		 need a layer for effect
	//AddGameObj<Billboard>(1)->SetPos({ 3.0f,2.0f,5.0f });

	m_bgm = AddGameObj<GameObject>(0)->AddComponent<Audio>();
	m_bgm->Load("asset\\audio\\bell.wav");
	m_bgm->Play(true);

	m_time = AddGameObj<Score>(2)->GetCount();

	fade = AddGameObj<Fade>(2);
}

void Game::UnInit()
{
	m_time = GetGameObj<Score>()->GetCount();

	Scene::UnInit();

	Bullet::UnLoad();
	SuperBullet::UnLoad();
	Enemy::UnLoad();
}

void Game::Update()
{
	Scene::Update();

	if (GetGameObj<Player>() == nullptr && m_finished == false) {
		fade->FadeOut();
		m_finished = true;
	}
	if (GetGameObj<EnemyCoward>() == nullptr 
		&& GetGameObj<Enemy>() == nullptr
		&& m_finished == false
		) {
		fade->FadeOut();
		m_finished = true;
	}

	if (fade->GetFadeFinished()) {
		for (int i = 0; i < 3; i++) {
			for (auto& g : m_GameObjs[i]) {
				g->Uninit();
			}
			m_GameObjs[i].clear();
		}
		
		Manager::SetScene<Finish>();
	}
}

