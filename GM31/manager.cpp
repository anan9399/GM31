#include "main.h"
#include "manager.h"
#include "renderer.h"
#include<wrl.h>
#include"Scene.h"
#include"Keyboard.h"
#include"Game.h"
#include"Title.h"
#include"audio.h"
std::shared_ptr<Scene> Manager::m_scene;
std::shared_ptr<Scene> Manager::m_nextScene;

void Manager::Init()
{
	Renderer::Init();
	Keyboard::Init();
	Audio::InitMaster();
	//m_Scene = std::make_shared<Title>();
	//m_Scene->Init();
	SetScene<Title>();
}

void Manager::Uninit()
{
	m_scene->UnInit();
	Keyboard::Uninit();
	Renderer::Uninit();
	Audio::UninitMaster();
	//m_Scene.reset();
}

void Manager::Update()
{
	Keyboard::Update();

	if (m_nextScene) {
		if (m_scene) {
			m_scene->UnInit();
			m_scene.reset();
		}

		m_scene = std::move(m_nextScene);
		m_scene->Init();
	}

	m_scene->Update();
}

void Manager::Draw()
{
	Renderer::Begin();
	
	m_scene->Draw();

	Renderer::End();
}
