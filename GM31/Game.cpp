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



std::mt19937 rng({ std::random_device{}() });
std::uniform_int_distribution<int> xdist(-40.0f, 40.0f);
std::uniform_int_distribution<int> ydist(0.0f, 2.0f);
std::uniform_int_distribution<int> zdist(-40.0f, 40.0f);

void Game::Init()
{

	AddGameObj<Camera>(0);
	AddGameObj<Field>(1)->SetPos({ 0.0f,0.0f,0.0f });


	AddGameObj<Player>(1);

	Billboard* b = AddGameObj<Billboard>(1);
	b->SetScale({ 2.0f,2.0f,2.0f });
	b->SetPos({ -5.0f,0.5f,5.0f });

	Box* box = AddGameObj<Box>(1);
	box->SetScale({ 10.0f,1.0f,2.0f });
	box->SetPos({ 10.0f,0.5f,-4.0f });


	Cylinder* cylinder = AddGameObj<Cylinder>(1);
	cylinder->SetScale({ 2.0f,2.0f,2.0f });
	cylinder->SetPos({ -13.0f,4.5f,4.0f });

	for (int i = 0; i < 20; i++) {
		box = AddGameObj<Box>(1);
		box->SetScale({ 2.0f,1.0f,2.0f });
		box->SetPos({ xdist(rng) + 1.0f,0.5f,zdist(rng)+1.0f });
	}
	

	AddGameObj<Enemy>(1)->SetPos({ -3.0f,2.5f,3.0f });
	AddGameObj<Enemy>(1)->SetPos({ 3.0f,2.5f,3.0f });
	AddGameObj<Enemy>(1)->SetPos({ 6.0f,2.5f,5.0f });

	// TODO: seperate the billboard to a new render query
	//		 need a layer for effect
	//AddGameObj<Billboard>(1)->SetPos({ 3.0f,2.0f,5.0f });

	m_bgm = AddGameObj<GameObject>(0)->AddComponent<Audio>();
	m_bgm->Load("asset\\audio\\bell.wav");
	m_bgm->Play(true);

	score = AddGameObj<Score>(2)->GetCount();
}

void Game::Update()
{
	Scene::Update();

	if (*score >= 15) {
		for (int i = 0; i < 3; i++) {
				for (auto& g : m_GameObjs[i]) {
				g->Uninit();
			}
			m_GameObjs[i].clear();
		}
		Manager::SetScene<Finish>();
	}
}

